// (c) Meta Platforms, Inc. and affiliates. Confidential and proprietary.

#include <deque>
#include "Ctran.h"
#include "CtranGpe.h"
#include "CtranMapper.h"
#include "comm.h"

thread_local std::deque<struct OpElem*> CtranOpGroup;

static ncclResult_t sendRecvImpl(
    std::vector<std::unique_ptr<struct OpElem>> opGroup) {
  ncclResult_t res = ncclSuccess;
  std::vector<struct OpElem*> sendOpGroup;

  std::vector<struct OpElem*> recvOpGroup;

  for (auto& op : opGroup) {
    if (op->type == OpElem::opType::SEND) {
      sendOpGroup.push_back(op.get());
    } else {
      recvOpGroup.push_back(op.get());
    }
  }

  std::vector<void*> sendMemHdl(sendOpGroup.size());
  std::vector<void*> remoteRecvBuff(sendOpGroup.size());
  std::vector<struct CtranMapperRemoteAccessKey> remoteAccessKey(
      sendOpGroup.size());
  std::vector<CtranMapperRequest*> sendCtrlReqs(sendOpGroup.size());
  std::vector<CtranMapperRequest*> putReqs(sendOpGroup.size());
  std::vector<bool> putIssued(sendOpGroup.size());

  std::vector<void*> recvMemHdl(recvOpGroup.size());
  std::vector<CtranMapperRequest*> recvCtrlReqs(recvOpGroup.size());
  std::vector<int> recvPeerRanks(recvOpGroup.size());
  std::unique_ptr<CtranMapperTimestamp> timestamp =
      std::unique_ptr<CtranMapperTimestamp>(
          new CtranMapperTimestamp("CtranSendRecv"));

  ncclComm_t comm = opGroup.front()->comm;

  std::vector<void*> tmpRegHdls;

  /* issue control messages for send operations */
  for (auto i = 0; i < sendOpGroup.size(); i++) {
    auto op = sendOpGroup[i];
    size_t sendSize = op->send.count * ncclTypeSize(op->send.datatype);
    bool localReg = false;

    NCCLCHECKGOTO(
        comm->ctran->mapper->searchRegHandle(
            op->send.sendbuff, sendSize, &sendMemHdl[i], &localReg),
        res,
        exit);
    if (localReg) {
      tmpRegHdls.push_back(sendMemHdl[i]);
    }

    NCCLCHECKGOTO(
        comm->ctran->mapper->irecvCtrl(
            &remoteRecvBuff[i],
            &remoteAccessKey[i],
            op->send.peerRank,
            &sendCtrlReqs[i]),
        res,
        exit);
    putIssued[i] = false;
  }

  /* issue control messages for recv operations */
  for (auto i = 0; i < recvOpGroup.size(); i++) {
    auto op = recvOpGroup[i];
    size_t recvSize = op->recv.count * ncclTypeSize(op->recv.datatype);
    bool localReg = false;

    NCCLCHECKGOTO(
        comm->ctran->mapper->searchRegHandle(
            op->recv.recvbuff, recvSize, &recvMemHdl[i], &localReg),
        res,
        exit);
    if (localReg) {
      tmpRegHdls.push_back(recvMemHdl[i]);
    }

    NCCLCHECKGOTO(
        comm->ctran->mapper->isendCtrl(
            op->recv.recvbuff,
            recvMemHdl[i],
            op->recv.peerRank,
            &recvCtrlReqs[i]),
        res,
        exit);
    recvPeerRanks[i] = op->recv.peerRank;
  }

  /* as we recv control msgs, issue PUT operations */
  while (1) {
    bool pendingOps = false;

    for (auto i = 0; i < sendOpGroup.size(); i++) {
      if (putIssued[i] == true) {
        continue;
      } else {
        auto op = sendOpGroup[i];
        size_t sendSize = op->send.count * ncclTypeSize(op->send.datatype);
        bool isComplete;

        NCCLCHECKGOTO(sendCtrlReqs[i]->test(&isComplete), res, exit);
        if (isComplete) {
          timestamp->recvCtrl.push_back(
              CtranMapperTimestampPoint(op->send.peerRank));
          NCCLCHECKGOTO(
              comm->ctran->mapper->iput(
                  op->send.sendbuff,
                  remoteRecvBuff[i],
                  sendSize,
                  op->send.peerRank,
                  sendMemHdl[i],
                  remoteAccessKey[i],
                  true,
                  &putReqs[i]),
              res,
              exit);
          timestamp->putIssued.push_back(
              CtranMapperTimestampPoint(op->send.peerRank));
          putIssued[i] = true;
        } else {
          pendingOps = true;
        }
      }
    }

    if (pendingOps == false) {
      break;
    }
  }

  /* wait for all PUT messages to complete */
  for (auto i = 0; i < sendOpGroup.size(); i++) {
    NCCLCHECKGOTO(putReqs[i]->wait(), res, exit);
    timestamp->putComplete.push_back(
        CtranMapperTimestampPoint(sendOpGroup[i]->send.peerRank));
  }

  /* wait for all control messages and notifications to complete */
  for (auto i = 0; i < recvOpGroup.size(); i++) {
    NCCLCHECKGOTO(recvCtrlReqs[i]->wait(), res, exit);
    NCCLCHECKGOTO(comm->ctran->mapper->waitNotify(recvPeerRanks[i]), res, exit);
  }

  /* deregister temporary registrations */
  for (auto hdl : tmpRegHdls) {
    NCCLCHECKGOTO(comm->ctran->mapper->deregMem(hdl), res, exit);
  }

  comm->ctran->mapper->timestamps.push_back(std::move(timestamp));
  comm->ctran->mapper->reportProfiling();

exit:
  return res;
}

bool ctranSendRecvSupport(int peer, ncclComm_t comm) {
  // TODO: conrrently support Ctran sendrecv only when peer is at remote node.
  // We will include intranode support when bringing in NVL backend.
  if (!ctranInitialized(comm) || comm->rankToNode[peer] == comm->node) {
    return false;
  } else {
    return true;
  }
}

ncclResult_t ctranSend(
    const void* sendbuff,
    size_t count,
    ncclDataType_t datatype,
    int peer,
    ncclComm_t comm,
    cudaStream_t stream) {
  CTRAN_COLL_INFO("CtranSend", sendbuff, count, datatype, peer, comm, stream);

  ncclResult_t res = ncclSuccess;
  struct OpElem* op;

  op = new struct OpElem;
  op->type = OpElem::opType::SEND;
  op->comm = comm;
  op->stream = stream;
  op->send.sendbuff = sendbuff;
  op->send.count = count;
  op->send.datatype = datatype;
  op->send.peerRank = peer;

  CtranOpGroup.push_back(op);

  return res;
}

ncclResult_t ctranRecv(
    void* recvbuff,
    size_t count,
    ncclDataType_t datatype,
    int peer,
    ncclComm_t comm,
    cudaStream_t stream) {
  CTRAN_COLL_INFO("CtranRecv", recvbuff, count, datatype, peer, comm, stream);

  ncclResult_t res = ncclSuccess;
  struct OpElem* op;

  op = new struct OpElem;
  op->type = OpElem::opType::RECV;
  op->comm = comm;
  op->stream = stream;
  op->recv.recvbuff = recvbuff;
  op->recv.count = count;
  op->recv.datatype = datatype;
  op->recv.peerRank = peer;

  CtranOpGroup.push_back(op);

  return res;
}

ncclResult_t ctranGroupEndHook(void) {
  ncclResult_t res = ncclSuccess;
  ncclComm_t comm;
  cudaStream_t stream;

  while (1) {
    std::vector<std::unique_ptr<struct OpElem>> toSubmit;
    std::deque<struct OpElem*> pending;
    bool hasSend = false;
    bool hasRecv = false;

    if (CtranOpGroup.empty()) {
      break;
    }

    comm = CtranOpGroup.front()->comm;
    stream = CtranOpGroup.front()->stream;
    while (!CtranOpGroup.empty()) {
      struct OpElem* op = CtranOpGroup.front();
      CtranOpGroup.pop_front();

      if (op->comm == comm && op->stream == stream) {
        toSubmit.push_back(std::unique_ptr<struct OpElem>(op));
        if (op->type == OpElem::opType::SEND) {
          hasSend = true;
        } else if (op->type == OpElem::opType::RECV) {
          hasRecv = true;
        }
      } else {
        pending.push_back(op);
      }
    }

    if (hasSend && hasRecv) {
      NCCLCHECKGOTO(
          comm->ctran->gpe->submit(
              std::move(toSubmit),
              sendRecvImpl,
              reinterpret_cast<void*>(ncclKernelSendRecv)),
          res,
          exit);
    } else if (hasSend) {
      NCCLCHECKGOTO(
          comm->ctran->gpe->submit(
              std::move(toSubmit),
              sendRecvImpl,
              reinterpret_cast<void*>(ncclKernelSend)),
          res,
          exit);
    } else if (hasRecv) {
      NCCLCHECKGOTO(
          comm->ctran->gpe->submit(
              std::move(toSubmit),
              sendRecvImpl,
              reinterpret_cast<void*>(ncclKernelRecv)),
          res,
          exit);
    }

    toSubmit.clear();
    CtranOpGroup = std::move(pending);
  }

exit:
  return res;
}