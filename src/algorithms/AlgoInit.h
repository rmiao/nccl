// (c) Meta Platforms, Inc. and affiliates. Confidential and proprietary.
#pragma once

#include "comm.h"
#include "nccl.h"

namespace nccl {
namespace algorithms {

// if forceInit==true, will init algoMgr regardless environment var
// NCCL_ALLREDUCE_ALGO=dda2 or not (useful for UT)
ncclResult_t algoInit(ncclComm_t comm, bool forceInit = false);

// this is needed as nccl calls free(comm) which won't deallocate
// unique_ptr algoMgr;
ncclResult_t algoDestroy(ncclComm_t comm);

} // namespace algorithms
} // namespace nccl
