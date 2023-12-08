// (c) Meta Platforms, Inc. and affiliates. Confidential and proprietary.

#include "all_reduce.h"
#include "all_reduce_dda2.h"
#include "collectives.h"
#include "common.h"

#define idx(nranks, i, j) ((i) * (nranks) + (j))

template <typename T>
static inline __device__ uint32_t
vecElementAdd(const uint32_t& a, const uint32_t& b) {
  if (std::is_same<T, half>::value) {
    const __half* x = reinterpret_cast<const __half*>(&a);
    const __half* y = reinterpret_cast<const __half*>(&b);

#if (__CUDA_ARCH__ >= 700)
    __half2 p = __halves2half2(x[0], x[1]);
    __half2 q = __halves2half2(y[0], y[1]);

    __half2 z = __hadd2(p, q);
    return (reinterpret_cast<uint32_t*>(&z))[0];
#else
    half z[2] = { __hadd(x[0], y[0]), __hadd(x[1], y[1]) };
    return (reinterpret_cast<uint32_t*>(z))[0];
#endif

#if defined(__CUDA_BF16_TYPES_EXIST__)
  } else if (std::is_same<T, __nv_bfloat16>::value) {
    const __nv_bfloat16* x = reinterpret_cast<const __nv_bfloat16*>(&a);
    const __nv_bfloat16* y = reinterpret_cast<const __nv_bfloat16*>(&b);

#if (__CUDA_ARCH__ >= 800)
    __nv_bfloat162 p = {x[0], x[1]};
    __nv_bfloat162 q = {y[0], y[1]};

    __nv_bfloat162 z = __hadd2(p, q);
    return (reinterpret_cast<uint32_t*>(&z))[0];
#else
    __nv_bfloat16 z[2] = {x[0] + y[0], x[1] + y[1]};
    return (reinterpret_cast<uint32_t*>(z))[0];
#endif
  }
#endif

  return 0;
}

/* create a special version of seqAdd that can be disabled at
 * compile-time for bfloat16 (using enable_if).  This is because the
 * base version of seqAdd does not compile for bfloat16, so we are
 * essentially tricking the compiler.  We never call this version for
 * bfloat16, so it doesn't matter that it does not compile, but the
 * compiler unfortunately does not know that. */
template <typename T, uint32_t NRANKS>
static inline __device__
typename std::enable_if<!std::is_same<T, half>::value
#if defined(__CUDA_BF16_TYPES_EXIST__)
    && !std::is_same<T, __nv_bfloat16>::value
#endif
    , uint4>::type
seqAdd(const T** src, size_t offset) {
  T dst[16 / sizeof(T)] = {0};
  for (int i = 0; i < NRANKS; i++) {
    uint4 vals = reinterpret_cast<const uint4*>(&src[i][offset])[0];
    const T* src_d = reinterpret_cast<const T*>(&vals);
    for (int j = 0; j < 16 / sizeof(T); j++) {
      dst[j] += src_d[j];
    }
  }
  return reinterpret_cast<uint4*>(&dst)[0];
}

template <typename T, uint32_t NRANKS>
static inline __device__
typename std::enable_if<std::is_same<T, half>::value
#if defined(__CUDA_BF16_TYPES_EXIST__)
    || std::is_same<T, __nv_bfloat16>::value
#endif
    , uint4>::type
seqAdd(const T** src, size_t offset) {
  uint4 x = {0, 0, 0, 0};

  return x;
}

template <typename T, uint32_t NRANKS>
static inline __device__ uint4 vecAdd(const T** src, size_t offset) {
  if (std::is_same<T, half>::value
#if defined(__CUDA_BF16_TYPES_EXIST__)
      || std::is_same<T, __nv_bfloat16>::value
#endif
  ) {
    uint4 dst = {0, 0, 0, 0};
    for (int i = 0; i < NRANKS; i++) {
      /* 16-byte load */
      uint4 vals = reinterpret_cast<const uint4*>(&src[i][offset])[0];

      /* vector additions */
      dst.x = vecElementAdd<T>(dst.x, vals.x);
      dst.y = vecElementAdd<T>(dst.y, vals.y);
      dst.z = vecElementAdd<T>(dst.z, vals.z);
      dst.w = vecElementAdd<T>(dst.w, vals.w);
    }
    return dst;
  } else {
    return seqAdd<T, NRANKS>(src, offset);
  }
}

template <typename T>
static inline __device__
typename std::enable_if<std::is_same<T, half>::value
#if defined(__CUDA_BF16_TYPES_EXIST__)
    || std::is_same<T, __nv_bfloat16>::value
#endif
    , uint4>::type
vecAdd(const T* src_a, const T* src_b) {
  /* 16-byte loads */
  uint4 vals_a = reinterpret_cast<const uint4*>(src_a)[0];
  uint4 vals_b = reinterpret_cast<const uint4*>(src_b)[0];

  /* vector additions */
  uint4 dst;
  dst.x = vecElementAdd<T>(vals_a.x, vals_b.x);
  dst.y = vecElementAdd<T>(vals_a.y, vals_b.y);
  dst.z = vecElementAdd<T>(vals_a.z, vals_b.z);
  dst.w = vecElementAdd<T>(vals_a.w, vals_b.w);
  return dst;
}

template <typename T>
static inline __device__
typename std::enable_if<!std::is_same<T, half>::value
#if defined(__CUDA_BF16_TYPES_EXIST__)
    && !std::is_same<T, __nv_bfloat16>::value
#endif
    , uint4>::type
vecAdd(const T* src_a, const T* src_b) {
  /* 16-byte loads */
  uint4 vals_a = reinterpret_cast<const uint4*>(src_a)[0];
  uint4 vals_b = reinterpret_cast<const uint4*>(src_b)[0];

  /* cast back to original type and do sequential additions */
  T dst[16 / sizeof(T)];
  const T* src_a_loaded = reinterpret_cast<const T*>(&vals_a);
  const T* src_b_loaded = reinterpret_cast<const T*>(&vals_b);
  for (int j = 0; j < 16 / sizeof(T); j++) {
    dst[j] = src_a_loaded[j] + src_b_loaded[j];
  }
  return reinterpret_cast<uint4*>(&dst)[0];
}

template <uint32_t NRANKS>
static inline __device__ void
barrier(uintptr_t* barrierMbox, uintptr_t barrierFlag, int rank) {
  volatile uintptr_t* barrier_d = barrierMbox;
  const int gtidx = threadIdx.x + blockDim.x * blockIdx.x;

  if (gtidx == 0) {
    barrier_d[rank] = barrierFlag;
  }

  if (threadIdx.x < NRANKS) {
    while ((barrier_d[threadIdx.x] & 1UL) != (barrierFlag & 1UL)) {
    }
  }

  /* remaining threads in the block wait */
  __syncthreads();
}

/*
 * We use a simple Allgather + local reduce algorithm here.  For small
 * messages, we are mostly latency bound on fast networks such as
 * NVLink.  So fetching data from all the GPUs simultaneously should
 * basically take the same amount of time as fetching data from one
 * GPU.  This algorithm directly reads data from the other GPUs and
 * reduces it into the local destination buffer.
 */
template <typename T, uint32_t NRANKS>
__global__ void ncclKernel_AllReduce_DDA2_Flat(
    uintptr_t barrierFlag,
    DdaDeviceState* devStates,
    int rank,
    const T* sendbuff,
    T* recvbuff,
    size_t count) {
  const int gtIdx = blockDim.x * blockIdx.x + threadIdx.x;

  // always use rank0's barrierMbox as the shared barrier
  uintptr_t* mbox = devStates[0].barrierMbox;
  barrier<NRANKS>(mbox, (reinterpret_cast<uintptr_t>(sendbuff)) | barrierFlag, rank);

  const T* srcs[NRANKS];
  for (int i = 0; i < NRANKS; i++) {
    int nbrRank = (rank + i) & (NRANKS - 1);
    srcs[i] = reinterpret_cast<const T*>(mbox[nbrRank] & ~1UL);
  }

  const size_t countPerThread = 16 / sizeof(T);
  const size_t idxStart = gtIdx * countPerThread;
  const size_t idxEnd = count;
  const size_t idxStride = gridDim.x * blockDim.x * countPerThread;

  for (size_t idx = idxStart; idx < idxEnd; idx += idxStride) {
    reinterpret_cast<uint4*>(&recvbuff[idx])[0] =
      vecAdd<T, NRANKS>(srcs, idx);
  }

  barrier<NRANKS>(mbox + NRANKS, barrierFlag, rank);
}

template <typename T, uint32_t NRANKS>
__global__ void ncclKernel_AllReduce_DDA2_Flat_ipc(
    uintptr_t barrierFlag,
    DdaDeviceState* devStates,
    int rank,
    T* recvbuff,
    size_t count) {
  const int gtIdx = blockDim.x * blockIdx.x + threadIdx.x;

  // always use rank0's barrierMbox as the shared barrier
  uintptr_t* mbox = devStates[0].barrierMbox;
  barrier<NRANKS>(mbox, barrierFlag, rank);

  const T* srcs[NRANKS];
  for (int i = 0; i < NRANKS; i++) {
    int nbrRank = (rank + i) & (NRANKS - 1);
    srcs[i] = reinterpret_cast<const T*>(devStates[nbrRank].tmpbuff);
  }

  const size_t countPerThread = 16 / sizeof(T);
  const size_t idxStart = gtIdx * countPerThread;
  const size_t idxEnd = count;
  const size_t idxStride = gridDim.x * blockDim.x * countPerThread;

  for (size_t idx = idxStart; idx < idxEnd; idx += idxStride) {
    reinterpret_cast<uint4*>(&recvbuff[idx])[0] =
      vecAdd<T, NRANKS>(srcs, idx);
  }

  barrier<NRANKS>(mbox + NRANKS, barrierFlag, rank);
}

template <typename T, uint32_t NRANKS>
static inline __device__ void reduceScatter(
    uintptr_t* mbox,
    uintptr_t barrierFlag,
    int rank,
    const T* sendbuff,
    T* recvbuff,
    size_t recvcount) {
  const int gtIdx = blockDim.x * blockIdx.x + threadIdx.x;

  // barrier to ensure every rank's sendbuff is ready to read
  barrier<NRANKS>(mbox, (reinterpret_cast<uintptr_t>(sendbuff)) | barrierFlag, rank);

  const T* srcs[NRANKS];
  for (int i = 0; i < NRANKS; ++i) {
    int nbrRank = (rank + i) & (NRANKS - 1);
    srcs[i] = reinterpret_cast<const T*>(mbox[nbrRank] & ~1UL);
  }

  // direct-access reduce data on rank-th block with 16-byte loads
  const size_t countPerThread = 16 / sizeof(T);
  const size_t idxStart = gtIdx * countPerThread;
  const size_t idxEnd = recvcount;
  const size_t idxStride = gridDim.x * blockDim.x * countPerThread;

  for (size_t idx = idxStart; idx < idxEnd; idx += idxStride) {
    reinterpret_cast<uint4*>(&recvbuff[idx])[0] =
        vecAdd<T, NRANKS>(srcs, idx + rank * recvcount);
  }
}

template <typename T, uint32_t NRANKS>
static inline __device__ void allGather(
    uintptr_t* mbox,
    uintptr_t barrierFlag,
    int rank,
    const T* sendbuff,
    T* recvbuff,
    size_t sendcount) {
  const int gtIdx = blockDim.x * blockIdx.x + threadIdx.x;

  // barrier to ensure every rank's sendbuff is ready to read
  barrier<NRANKS>(mbox, (reinterpret_cast<uintptr_t>(sendbuff)) | barrierFlag, rank);

  const T* srcs[NRANKS];
  int rankOffset[NRANKS];
  for (int i = 0; i < NRANKS; ++i) {
    int nbrRank = (rank + i) & (NRANKS - 1);
    srcs[i] = reinterpret_cast<const T*>(mbox[nbrRank] & ~1UL);
    rankOffset[i] = nbrRank * sendcount;
  }

  // direct-access all-gather with 16-byte loads
  const size_t countPerThread = 16 / sizeof(T);
  const size_t idxStart = gtIdx * countPerThread;
  const size_t idxEnd = sendcount;
  const size_t idxStride = gridDim.x * blockDim.x * countPerThread;

  for (int i = 0; i < NRANKS; ++i) {
    for (size_t idx = idxStart; idx < idxEnd; idx += idxStride) {
      reinterpret_cast<uint4*>(&recvbuff[idx + rankOffset[i]])[0] = reinterpret_cast<const uint4*>(&srcs[i][idx])[0];
    }
  }
}

/*
 * Hierarchical algorithm for large messages.  In this algorithm, we
 * avoid every rank fetching all of the data from every other rank
 * that the flat algorithm above does.  Instead, we do two steps:
 * - step1: (reduce-scatter)
 * each rank fetches only a subset of data
 * from all other ranks and reduces locally.
 * - step2: (all-gather)
 * Then we do a second step where the reduced data is Allgathered (by
 * direct copy by each rank).
 */
template <typename T, uint32_t NRANKS>
__global__ void ncclKernel_AllReduce_DDA2_Tree(
    uintptr_t barrierFlag,
    DdaDeviceState* devStates,
    int rank,
    const T* sendbuff,
    T* recvbuff,
    size_t count) {
  // always use rank0's barrierMbox as the shared barrier
  uintptr_t* mbox = devStates[0].barrierMbox;

  const size_t chunkSize = count / NRANKS;
  reduceScatter<T, NRANKS>(mbox, barrierFlag, rank, sendbuff, recvbuff + rank * chunkSize, chunkSize);

  // make sure the result from RS are observed by all threads in peer devices
  __threadfence_system();
  allGather<T, NRANKS>(mbox + NRANKS, barrierFlag, rank, recvbuff + rank * chunkSize, recvbuff, chunkSize);

  barrier<NRANKS>(mbox + 2 * NRANKS, barrierFlag, rank);
}

DECL_DDA2_FUNC(char);
DECL_DDA2_FUNC(uint8_t);
DECL_DDA2_FUNC(int32_t);
DECL_DDA2_FUNC(uint32_t);
DECL_DDA2_FUNC(int64_t);
DECL_DDA2_FUNC(uint64_t);
DECL_DDA2_FUNC(half);
DECL_DDA2_FUNC(float);
DECL_DDA2_FUNC(double);
#if defined(__CUDA_BF16_TYPES_EXIST__)
DECL_DDA2_FUNC(__nv_bfloat16);
#endif
