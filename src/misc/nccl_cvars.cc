// (c) Meta Platforms, Inc. and affiliates. Confidential and proprietary.

#include <sys/syscall.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <vector>
#include <cstring>
#include "nccl_cvars.h"
#include "debug.h"
#include "checks.h"

/**
* Cvar template source file.
* It initializes control variables for NCCL at environment initialization time.
* Partial contents are auto-generated by ./maint/extractcvars.py
* See ## CONTENTS ## in nccl_cvars.cc.in
*/

// Cvar internal logger
// We need avoid calling into default logger because it may call ncclGetEnv() on
// demand in ncclDebugInit() and cause circular call & deadlock. Since CVAR_WARN
// happens usually only at initialization time and is for warning only, we might
// be OK to use separate logger here and always print to stdout.
static int pid = getpid();
static thread_local int tid = syscall(SYS_gettid);
static char hostname[1024];
static bool enableCvarWarn = true;
static int cudaDev = -1;

#define CVAR_WARN(fmt, ...)                                 \
  if (enableCvarWarn) {                                     \
    printf(                                                 \
        "%s %s:%d:%d [%d] %s:%d NCCL WARN CVAR: " fmt "\n", \
        getTime().c_str(),                                  \
        hostname,                                           \
        pid,                                                \
        tid,                                                \
        cudaDev,                                            \
        __FUNCTION__,                                       \
        __LINE__,                                           \
        ##__VA_ARGS__);                                     \
  }

#define CVAR_WARN_UNKNOWN_VALUE(name, value)               \
  do {                                                     \
    CVAR_WARN("Unknown value %s for env %s", value, name); \
  } while (0)

static void initCvarLogger() {
  const char* nccl_debug = getenv("NCCL_DEBUG");
  if (nccl_debug == NULL || strcasecmp(nccl_debug, "VERSION") == 0) {
    enableCvarWarn = false;
  }
  getHostName(hostname, 1024, '.');

  // Used for ncclCvarInit time warning only
  CUDACHECKIGNORE(cudaGetDevice(&cudaDev));
}

// trim from start (in place)
static inline void ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
    return !std::isspace(ch);
  }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
    return !std::isspace(ch);
  }).base(), s.end());
}

static std::vector<std::string> tokenizer(std::string str) {
  std::string delim = ",";
  std::vector<std::string> tokens;

  while (auto pos = str.find(",")) {
    std::string newstr = str.substr(0, pos);
    ltrim(newstr);
    rtrim(newstr);
    // Skip empty string
    if(!newstr.empty()) {
      if(std::find(tokens.begin(), tokens.end(), newstr) != tokens.end()) {
        CVAR_WARN("Duplicate token %s found in the value of %s", newstr.c_str(), str.c_str());
      }
      tokens.push_back(newstr);
    }
    str.erase(0, pos + delim.length());
    if (pos == std::string::npos) {
      break;
    }
  }
  return tokens;
}

static bool env2bool(const char *str_, const char *def) {
  std::string str(getenv(str_) ? getenv(str_) : def);
  std::transform(str.cbegin(), str.cend(), str.begin(), [](unsigned char c) { return std::tolower(c); });
  if (str == "y") return true;
  else if (str == "n") return false;
  else if (str == "yes") return true;
  else if (str == "no") return false;
  else if (str == "t") return true;
  else if (str == "f") return false;
  else if (str == "true") return true;
  else if (str == "false") return false;
  else if (str == "1") return true;
  else if (str == "0") return false;
  else CVAR_WARN_UNKNOWN_VALUE(str_, str.c_str());
  return true;
}

static int env2int(const char *str, const char *def) {
  return getenv(str) ? atoi(getenv(str)) : atoi(def);
}

static std::string env2str(const char *str, const char *def_) {
  const char *def = def_ ? def_ : "";
  std::string str_s = getenv(str) ? std::string(getenv(str)) : std::string(def);
  ltrim(str_s);
  rtrim(str_s);
  return str_s;
}

static std::vector<std::string> env2strlist(const char* str, const char* def_) {
  const char* def = def_ ? def_ : "";
  std::string str_s(getenv(str) ? getenv(str) : def);
  return tokenizer(str_s);
}

std::tuple<std::string, std::vector<std::string>> env2prefixedStrlist(
    const char* str,
    const char* def_,
    std::vector<std::string> prefixes) {
  const char* def = def_ ? def_ : "";
  std::string str_s(getenv(str) ? getenv(str) : def);

  // search if any prefix is specified
  for (auto prefix : prefixes) {
    if (!str_s.compare(0, prefix.size(), prefix)) {
      // if prefix is found, convert the remaining string to stringList
      std::string slist_s = str_s.substr(prefix.size());
      return std::make_tuple(prefix, tokenizer(slist_s));
    }
  }
  // if no prefix is found, convert entire string to stringList
  return std::make_tuple("", tokenizer(str_s));
}

// Automatically generated by ./maint/extractcvars.py --- START
// DO NOT EDIT!!!
enum NCCL_ALLGATHER_ALGO NCCL_ALLGATHER_ALGO;

int NCCL_ALLGATHER_DIRECT_CUTOFF;

enum NCCL_ALLREDUCE_ALGO NCCL_ALLREDUCE_ALGO;

enum NCCL_ALLREDUCE_ALGO2 NCCL_ALLREDUCE_ALGO2;

int NCCL_ALLREDUCE_SPARSE_BLOCK_NUM_THREAD_BLOCKS;

int NCCL_ALLREDUCE_SPARSE_BLOCK_THREAD_BLOCK_SIZE;

std::vector<enum NCCL_CTRAN_BACKENDS> NCCL_CTRAN_BACKENDS;

int NCCL_CTRAN_IB_MAX_QPS;

int NCCL_CTRAN_IB_QP_SCALING_THRESHOLD;

bool NCCL_CTRAN_IB_TRAFFIC_PROFILNG;

std::string NCCL_CTRAN_KINETO_PROFILE_DIR;

enum NCCL_CTRAN_PROFILING NCCL_CTRAN_PROFILING;

int NCCL_CTRAN_PROFILING_REPORT_COUNT;

enum NCCL_CTRAN_REGISTER NCCL_CTRAN_REGISTER;

int NCCL_CTRAN_REGISTER_REPORT_SNAPSHOT_COUNT;

std::string NCCL_CTRAN_TOPO_FILE;

std::vector<std::string> NCCL_CTRAN_TOPO_FILE_KEYS;

int NCCL_DDA2_ALLREDUCE_MAX_BLOCKS;

int NCCL_DDA2_ALLREDUCE_TMPBUFF_SIZE;

int NCCL_DDA2_ALLREDUCE_TREE_THRESHOLD_NVS;

bool NCCL_DDA_ALLREDUCE_LARGE_MESSAGE_HCM;

int NCCL_DDA_ALLREDUCE_MAX_BLOCKS;

int NCCL_DDA_ALLREDUCE_TMPBUFF_SIZE;

int NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_HCM;

int NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_NVS;

bool NCCL_DDA_FORCE_P2P_ACCESS;

int NCCL_DDA_MAX_RANKS;

std::string NCCL_IB_HCA_PREFIX;
std::vector<std::string> NCCL_IB_HCA;

enum NCCL_SENDRECV_ALGO NCCL_SENDRECV_ALGO;

// Automatically generated by ./maint/extractcvars.py --- END


extern char **environ;
static std::unordered_set<std::string> env;

// Automatically generated by ./maint/extractcvars.py --- START
// DO NOT EDIT!!!
void initEnvSet() {
  env.insert("NCCL_ALLGATHER_ALGO");
  env.insert("NCCL_ALLGATHER_DIRECT_CUTOFF");
  env.insert("NCCL_ALLREDUCE_ALGO");
  env.insert("NCCL_ALLREDUCE_ALGO2");
  env.insert("NCCL_ALLREDUCE_SPARSE_BLOCK_NUM_THREAD_BLOCKS");
  env.insert("NCCL_ALLREDUCE_SPARSE_BLOCK_THREAD_BLOCK_SIZE");
  env.insert("NCCL_CTRAN_BACKENDS");
  env.insert("NCCL_CTRAN_IB_MAX_QPS");
  env.insert("NCCL_CTRAN_IB_QP_SCALING_THRESHOLD");
  env.insert("NCCL_CTRAN_IB_TRAFFIC_PROFILNG");
  env.insert("NCCL_CTRAN_KINETO_PROFILE_DIR");
  env.insert("NCCL_CTRAN_PROFILING");
  env.insert("NCCL_CTRAN_PROFILING_REPORT_COUNT");
  env.insert("NCCL_CTRAN_REGISTER");
  env.insert("NCCL_CTRAN_REGISTER_REPORT_SNAPSHOT_COUNT");
  env.insert("NCCL_CTRAN_TOPO_FILE");
  env.insert("NCCL_CTRAN_TOPO_FILE_KEYS");
  env.insert("NCCL_DDA2_ALLREDUCE_MAX_BLOCKS");
  env.insert("NCCL_DDA2_ALLREDUCE_TMPBUFF_SIZE");
  env.insert("NCCL_DDA2_ALLREDUCE_TREE_THRESHOLD_NVS");
  env.insert("NCCL_DDA_ALLREDUCE_LARGE_MESSAGE_HCM");
  env.insert("NCCL_DDA_ALLREDUCE_MAX_BLOCKS");
  env.insert("NCCL_DDA_ALLREDUCE_TMPBUFF_SIZE");
  env.insert("NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_HCM");
  env.insert("NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_NVS");
  env.insert("NCCL_DDA_FORCE_P2P_ACCESS");
  env.insert("NCCL_DDA_MAX_RANKS");
  env.insert("NCCL_IB_HCA");
  env.insert("NCCL_SENDRECV_ALGO");
  env.insert("NCCL_ALGO");
  env.insert("NCCL_COLLNET_ENABLE");
  env.insert("NCCL_COLLTRACE_LOCAL_SUBDIR");
  env.insert("NCCL_COMM_ID");
  env.insert("NCCL_CUDA_PATH");
  env.insert("NCCL_CROSS_NIC");
  env.insert("NCCL_DEBUG");
  env.insert("NCCL_DEBUG_FILE");
  env.insert("NCCL_DEBUG_SUBSYS");
  env.insert("NCCL_GRAPH_DUMP_FILE");
  env.insert("NCCL_GRAPH_FILE");
  env.insert("NCCL_HOSTID");
  env.insert("NCCL_IB_DISABLE");
  env.insert("NCCL_IB_GID_INDEX");
  env.insert("NCCL_IB_TC");
  env.insert("NCCL_IB_TIMEOUT");
  env.insert("NCCL_IB_QPS_PER_CONNECTION");
  env.insert("NCCL_LAUNCH_MODE");
  env.insert("NCCL_NET");
  env.insert("NCCL_NET_PLUGIN");
  env.insert("NCCL_NET_SHARED_COMMS");
  env.insert("NCCL_NSOCKS_PERTHREAD");
  env.insert("NCCL_PROTO");
  env.insert("NCCL_PROXY_PROFILE");
  env.insert("NCCL_PXN_DISABLE");
  env.insert("NCCL_P2P_LEVEL");
  env.insert("NCCL_SHM_DISABLE");
  env.insert("NCCL_SOCKET_FAMILY");
  env.insert("NCCL_SOCKET_IFNAME");
  env.insert("NCCL_SOCKET_NTHREADS");
  env.insert("NCCL_THREAD_THRESHOLDS");
  env.insert("NCCL_TOPO_DUMP_FILE");
  env.insert("NCCL_TOPO_FILE");
  env.insert("NCCL_TUNER_PLUGIN");
}
// Automatically generated by ./maint/extractcvars.py --- END


// Automatically generated by ./maint/extractcvars.py --- START
// DO NOT EDIT!!!
void readCvarEnv() {
  if (getenv("NCCL_ALLGATHER_ALGO") == nullptr) {
    NCCL_ALLGATHER_ALGO = NCCL_ALLGATHER_ALGO::orig;
  } else {
    std::string str(getenv("NCCL_ALLGATHER_ALGO"));
    if (str == std::string("orig")) {
      NCCL_ALLGATHER_ALGO = NCCL_ALLGATHER_ALGO::orig;
    } else if (str == std::string("ctdirect")) {
      NCCL_ALLGATHER_ALGO = NCCL_ALLGATHER_ALGO::ctdirect;
    } else if (str == std::string("ctring")) {
      NCCL_ALLGATHER_ALGO = NCCL_ALLGATHER_ALGO::ctring;
    } else if (str == std::string("ctrd")) {
      NCCL_ALLGATHER_ALGO = NCCL_ALLGATHER_ALGO::ctrd;
    } else {
      CVAR_WARN_UNKNOWN_VALUE("NCCL_ALLGATHER_ALGO", str.c_str());
    }
  }

  NCCL_ALLGATHER_DIRECT_CUTOFF = env2int("NCCL_ALLGATHER_DIRECT_CUTOFF", "524288");

  if (getenv("NCCL_ALLREDUCE_ALGO") == nullptr) {
    NCCL_ALLREDUCE_ALGO = NCCL_ALLREDUCE_ALGO::orig;
  } else {
    std::string str(getenv("NCCL_ALLREDUCE_ALGO"));
    if (str == std::string("orig")) {
      NCCL_ALLREDUCE_ALGO = NCCL_ALLREDUCE_ALGO::orig;
    } else if (str == std::string("dda")) {
      NCCL_ALLREDUCE_ALGO = NCCL_ALLREDUCE_ALGO::dda;
    } else {
      CVAR_WARN_UNKNOWN_VALUE("NCCL_ALLREDUCE_ALGO", str.c_str());
    }
  }

  if (getenv("NCCL_ALLREDUCE_ALGO2") == nullptr) {
    NCCL_ALLREDUCE_ALGO2 = NCCL_ALLREDUCE_ALGO2::orig;
  } else {
    std::string str(getenv("NCCL_ALLREDUCE_ALGO2"));
    if (str == std::string("orig")) {
      NCCL_ALLREDUCE_ALGO2 = NCCL_ALLREDUCE_ALGO2::orig;
    } else if (str == std::string("dda")) {
      NCCL_ALLREDUCE_ALGO2 = NCCL_ALLREDUCE_ALGO2::dda;
    } else {
      CVAR_WARN_UNKNOWN_VALUE("NCCL_ALLREDUCE_ALGO2", str.c_str());
    }
  }

  NCCL_ALLREDUCE_SPARSE_BLOCK_NUM_THREAD_BLOCKS = env2int("NCCL_ALLREDUCE_SPARSE_BLOCK_NUM_THREAD_BLOCKS", "-1");

  NCCL_ALLREDUCE_SPARSE_BLOCK_THREAD_BLOCK_SIZE = env2int("NCCL_ALLREDUCE_SPARSE_BLOCK_THREAD_BLOCK_SIZE", "-1");

  {
    NCCL_CTRAN_BACKENDS.clear();
    auto tokens = env2strlist("NCCL_CTRAN_BACKENDS", "ib");
    for (auto token : tokens) {
      if (token == std::string("ib")) {
        NCCL_CTRAN_BACKENDS.emplace_back(NCCL_CTRAN_BACKENDS::ib);
      } else {
        CVAR_WARN_UNKNOWN_VALUE("NCCL_CTRAN_BACKENDS", token.c_str());
      }
    }
  }

  NCCL_CTRAN_IB_MAX_QPS = env2int("NCCL_CTRAN_IB_MAX_QPS", "1");

  NCCL_CTRAN_IB_QP_SCALING_THRESHOLD = env2int("NCCL_CTRAN_IB_QP_SCALING_THRESHOLD", "1048576");

  NCCL_CTRAN_IB_TRAFFIC_PROFILNG = env2bool("NCCL_CTRAN_IB_TRAFFIC_PROFILNG", "False");

  NCCL_CTRAN_KINETO_PROFILE_DIR = env2str("NCCL_CTRAN_KINETO_PROFILE_DIR", "/tmp");

  if (getenv("NCCL_CTRAN_PROFILING") == nullptr) {
    NCCL_CTRAN_PROFILING = NCCL_CTRAN_PROFILING::none;
  } else {
    std::string str(getenv("NCCL_CTRAN_PROFILING"));
    if (str == std::string("none")) {
      NCCL_CTRAN_PROFILING = NCCL_CTRAN_PROFILING::none;
    } else if (str == std::string("stdout")) {
      NCCL_CTRAN_PROFILING = NCCL_CTRAN_PROFILING::stdout;
    } else if (str == std::string("info")) {
      NCCL_CTRAN_PROFILING = NCCL_CTRAN_PROFILING::info;
    } else if (str == std::string("kineto")) {
      NCCL_CTRAN_PROFILING = NCCL_CTRAN_PROFILING::kineto;
    } else {
      CVAR_WARN_UNKNOWN_VALUE("NCCL_CTRAN_PROFILING", str.c_str());
    }
  }

  NCCL_CTRAN_PROFILING_REPORT_COUNT = env2int("NCCL_CTRAN_PROFILING_REPORT_COUNT", "100");

  if (getenv("NCCL_CTRAN_REGISTER") == nullptr) {
    NCCL_CTRAN_REGISTER = NCCL_CTRAN_REGISTER::lazy;
  } else {
    std::string str(getenv("NCCL_CTRAN_REGISTER"));
    if (str == std::string("none")) {
      NCCL_CTRAN_REGISTER = NCCL_CTRAN_REGISTER::none;
    } else if (str == std::string("lazy")) {
      NCCL_CTRAN_REGISTER = NCCL_CTRAN_REGISTER::lazy;
    } else if (str == std::string("eager")) {
      NCCL_CTRAN_REGISTER = NCCL_CTRAN_REGISTER::eager;
    } else {
      CVAR_WARN_UNKNOWN_VALUE("NCCL_CTRAN_REGISTER", str.c_str());
    }
  }

  NCCL_CTRAN_REGISTER_REPORT_SNAPSHOT_COUNT = env2int("NCCL_CTRAN_REGISTER_REPORT_SNAPSHOT_COUNT", "-1");

  NCCL_CTRAN_TOPO_FILE = env2str("NCCL_CTRAN_TOPO_FILE", "");

  NCCL_CTRAN_TOPO_FILE_KEYS.clear();
  NCCL_CTRAN_TOPO_FILE_KEYS = env2strlist("NCCL_CTRAN_TOPO_FILE_KEYS", "");

  NCCL_DDA2_ALLREDUCE_MAX_BLOCKS = env2int("NCCL_DDA2_ALLREDUCE_MAX_BLOCKS", "24");

  NCCL_DDA2_ALLREDUCE_TMPBUFF_SIZE = env2int("NCCL_DDA2_ALLREDUCE_TMPBUFF_SIZE", "33554432");

  NCCL_DDA2_ALLREDUCE_TREE_THRESHOLD_NVS = env2int("NCCL_DDA2_ALLREDUCE_TREE_THRESHOLD_NVS", "262144");

  NCCL_DDA_ALLREDUCE_LARGE_MESSAGE_HCM = env2bool("NCCL_DDA_ALLREDUCE_LARGE_MESSAGE_HCM", "False");

  NCCL_DDA_ALLREDUCE_MAX_BLOCKS = env2int("NCCL_DDA_ALLREDUCE_MAX_BLOCKS", "1");

  NCCL_DDA_ALLREDUCE_TMPBUFF_SIZE = env2int("NCCL_DDA_ALLREDUCE_TMPBUFF_SIZE", "33554432");

  NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_HCM = env2int("NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_HCM", "65536");

  NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_NVS = env2int("NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_NVS", "262144");

  NCCL_DDA_FORCE_P2P_ACCESS = env2bool("NCCL_DDA_FORCE_P2P_ACCESS", "False");

  NCCL_DDA_MAX_RANKS = env2int("NCCL_DDA_MAX_RANKS", "16");

  std::vector<std::string> NCCL_IB_HCA_allPrefixes{"^", "="};
  NCCL_IB_HCA.clear();
  std::tie(NCCL_IB_HCA_PREFIX, NCCL_IB_HCA) = env2prefixedStrlist("NCCL_IB_HCA", "", NCCL_IB_HCA_allPrefixes);

  if (getenv("NCCL_SENDRECV_ALGO") == nullptr) {
    NCCL_SENDRECV_ALGO = NCCL_SENDRECV_ALGO::orig;
  } else {
    std::string str(getenv("NCCL_SENDRECV_ALGO"));
    if (str == std::string("orig")) {
      NCCL_SENDRECV_ALGO = NCCL_SENDRECV_ALGO::orig;
    } else if (str == std::string("ctran")) {
      NCCL_SENDRECV_ALGO = NCCL_SENDRECV_ALGO::ctran;
    } else {
      CVAR_WARN_UNKNOWN_VALUE("NCCL_SENDRECV_ALGO", str.c_str());
    }
  }

}
// Automatically generated by ./maint/extractcvars.py --- END


void ncclCvarInit() {
  initEnvSet();

  initCvarLogger();

  // Check if any NCCL_ env var is not in allow list
  char **s = environ;
  for (; *s; s++) {
    if (!strncmp(*s, "NCCL_", strlen("NCCL_"))) {
      std::string str(*s);
      str = str.substr(0, str.find("="));
      if (env.find(str) == env.end()) {
        CVAR_WARN("Unknown env %s in the NCCL namespace", str.c_str());
      }
    }
  }

  readCvarEnv();
}
