// (c) Meta Platforms, Inc. and affiliates. Confidential and proprietary.

#include <gtest/gtest.h>
#include <set>
#include <vector>
#include <nccl.h>
#include <stdlib.h>
#include "../include/nccl_cvars.h"

class NCCLEnvironment : public ::testing::Environment {
 public:
  void SetUp() override {
    // Turn off NCCL debug logging, allow user to turn on via command line
    setenv("NCCL_DEBUG", "WARN", 0);
  }
  ~NCCLEnvironment() override {}
};

class CvarTest : public ::testing::Test {
 public:
  CvarTest() = default;
};

/**
* Utility functions
*/
template <typename T>
void checkListValues(std::vector<T> vals, std::vector<T> cvar) {
  for (int i = 0; i < vals.size(); i++) {
    EXPECT_EQ(cvar[i], vals[i]);
  }
}

void testDefaultValue(const char* cvarName) {
  unsetenv(cvarName);
  ncclCvarInit();
}

void testIntValue(const char* cvarName, int val) {
  std::ostringstream varOSS;
  varOSS << val;
  std::string varStr = varOSS.str();
  setenv(cvarName, varStr.c_str(), 1);
  ncclCvarInit();
}

/**
* START of generated tests
*/

// Automatically generated by ./maint/extractcvars.py
// DO NOT EDIT!!!
TEST_F(CvarTest, NCCL_DDA_ALLREDUCE_LARGE_MESSAGE_HCM_value_y0) {
  setenv("NCCL_DDA_ALLREDUCE_LARGE_MESSAGE_HCM", "y", 1);
  ncclCvarInit();
  EXPECT_TRUE(NCCL_DDA_ALLREDUCE_LARGE_MESSAGE_HCM);
}

TEST_F(CvarTest, NCCL_DDA_ALLREDUCE_LARGE_MESSAGE_HCM_value_y1) {
  setenv("NCCL_DDA_ALLREDUCE_LARGE_MESSAGE_HCM", "yes", 1);
  ncclCvarInit();
  EXPECT_TRUE(NCCL_DDA_ALLREDUCE_LARGE_MESSAGE_HCM);
}

TEST_F(CvarTest, NCCL_DDA_ALLREDUCE_LARGE_MESSAGE_HCM_value_y2) {
  setenv("NCCL_DDA_ALLREDUCE_LARGE_MESSAGE_HCM", "true", 1);
  ncclCvarInit();
  EXPECT_TRUE(NCCL_DDA_ALLREDUCE_LARGE_MESSAGE_HCM);
}

TEST_F(CvarTest, NCCL_DDA_ALLREDUCE_LARGE_MESSAGE_HCM_value_y3) {
  setenv("NCCL_DDA_ALLREDUCE_LARGE_MESSAGE_HCM", "1", 1);
  ncclCvarInit();
  EXPECT_TRUE(NCCL_DDA_ALLREDUCE_LARGE_MESSAGE_HCM);
}

TEST_F(CvarTest, NCCL_DDA_ALLREDUCE_LARGE_MESSAGE_HCM_value_n0) {
  setenv("NCCL_DDA_ALLREDUCE_LARGE_MESSAGE_HCM", "n", 1);
  ncclCvarInit();
  EXPECT_FALSE(NCCL_DDA_ALLREDUCE_LARGE_MESSAGE_HCM);
}

TEST_F(CvarTest, NCCL_DDA_ALLREDUCE_LARGE_MESSAGE_HCM_value_n1) {
  setenv("NCCL_DDA_ALLREDUCE_LARGE_MESSAGE_HCM", "no", 1);
  ncclCvarInit();
  EXPECT_FALSE(NCCL_DDA_ALLREDUCE_LARGE_MESSAGE_HCM);
}

TEST_F(CvarTest, NCCL_DDA_ALLREDUCE_LARGE_MESSAGE_HCM_value_n2) {
  setenv("NCCL_DDA_ALLREDUCE_LARGE_MESSAGE_HCM", "false", 1);
  ncclCvarInit();
  EXPECT_FALSE(NCCL_DDA_ALLREDUCE_LARGE_MESSAGE_HCM);
}

TEST_F(CvarTest, NCCL_DDA_ALLREDUCE_LARGE_MESSAGE_HCM_value_n3) {
  setenv("NCCL_DDA_ALLREDUCE_LARGE_MESSAGE_HCM", "0", 1);
  ncclCvarInit();
  EXPECT_FALSE(NCCL_DDA_ALLREDUCE_LARGE_MESSAGE_HCM);
}

TEST_F(CvarTest, NCCL_DDA_ALLREDUCE_TMPBUFF_SIZE_value_0) {
  testIntValue("NCCL_DDA_ALLREDUCE_TMPBUFF_SIZE", -100);
  EXPECT_EQ(NCCL_DDA_ALLREDUCE_TMPBUFF_SIZE, -100);
}

TEST_F(CvarTest, NCCL_DDA_ALLREDUCE_TMPBUFF_SIZE_value_1) {
  testIntValue("NCCL_DDA_ALLREDUCE_TMPBUFF_SIZE", 0);
  EXPECT_EQ(NCCL_DDA_ALLREDUCE_TMPBUFF_SIZE, 0);
}

TEST_F(CvarTest, NCCL_DDA_ALLREDUCE_TMPBUFF_SIZE_value_2) {
  testIntValue("NCCL_DDA_ALLREDUCE_TMPBUFF_SIZE", 9999);
  EXPECT_EQ(NCCL_DDA_ALLREDUCE_TMPBUFF_SIZE, 9999);
}

TEST_F(CvarTest, NCCL_DDA_ALLREDUCE_TMPBUFF_SIZE_value_3) {
  testIntValue("NCCL_DDA_ALLREDUCE_TMPBUFF_SIZE", INT_MAX);
  EXPECT_EQ(NCCL_DDA_ALLREDUCE_TMPBUFF_SIZE, INT_MAX);
}

TEST_F(CvarTest, NCCL_DDA_ALLREDUCE_TMPBUFF_SIZE_value_4) {
  testIntValue("NCCL_DDA_ALLREDUCE_TMPBUFF_SIZE", INT_MIN);
  EXPECT_EQ(NCCL_DDA_ALLREDUCE_TMPBUFF_SIZE, INT_MIN);
}

TEST_F(CvarTest, NCCL_DDA_ALLREDUCE_TMPBUFF_SIZE_default_value) {
  testDefaultValue("NCCL_DDA_ALLREDUCE_TMPBUFF_SIZE");
  EXPECT_EQ(NCCL_DDA_ALLREDUCE_TMPBUFF_SIZE, 33554432);
}

TEST_F(CvarTest, NCCL_DDA_MAX_RANKS_value_0) {
  testIntValue("NCCL_DDA_MAX_RANKS", -100);
  EXPECT_EQ(NCCL_DDA_MAX_RANKS, -100);
}

TEST_F(CvarTest, NCCL_DDA_MAX_RANKS_value_1) {
  testIntValue("NCCL_DDA_MAX_RANKS", 0);
  EXPECT_EQ(NCCL_DDA_MAX_RANKS, 0);
}

TEST_F(CvarTest, NCCL_DDA_MAX_RANKS_value_2) {
  testIntValue("NCCL_DDA_MAX_RANKS", 9999);
  EXPECT_EQ(NCCL_DDA_MAX_RANKS, 9999);
}

TEST_F(CvarTest, NCCL_DDA_MAX_RANKS_value_3) {
  testIntValue("NCCL_DDA_MAX_RANKS", INT_MAX);
  EXPECT_EQ(NCCL_DDA_MAX_RANKS, INT_MAX);
}

TEST_F(CvarTest, NCCL_DDA_MAX_RANKS_value_4) {
  testIntValue("NCCL_DDA_MAX_RANKS", INT_MIN);
  EXPECT_EQ(NCCL_DDA_MAX_RANKS, INT_MIN);
}

TEST_F(CvarTest, NCCL_DDA_MAX_RANKS_default_value) {
  testDefaultValue("NCCL_DDA_MAX_RANKS");
  EXPECT_EQ(NCCL_DDA_MAX_RANKS, 16);
}

TEST_F(CvarTest, NCCL_ALLREDUCE_ALGO_single_choice_0) {
  setenv("NCCL_ALLREDUCE_ALGO", "orig", 1);
  ncclCvarInit();
  EXPECT_EQ(NCCL_ALLREDUCE_ALGO, NCCL_ALLREDUCE_ALGO::orig);
}

TEST_F(CvarTest, NCCL_ALLREDUCE_ALGO_single_choice_1) {
  setenv("NCCL_ALLREDUCE_ALGO", "dda", 1);
  ncclCvarInit();
  EXPECT_EQ(NCCL_ALLREDUCE_ALGO, NCCL_ALLREDUCE_ALGO::dda);
}

TEST_F(CvarTest, NCCL_ALLREDUCE_ALGO_default_choice) {
  testDefaultValue("NCCL_ALLREDUCE_ALGO");
  EXPECT_EQ(NCCL_ALLREDUCE_ALGO, NCCL_ALLREDUCE_ALGO::orig);
}

TEST_F(CvarTest, NCCL_ALLREDUCE_ALGO2_single_choice_0) {
  setenv("NCCL_ALLREDUCE_ALGO2", "orig", 1);
  ncclCvarInit();
  EXPECT_EQ(NCCL_ALLREDUCE_ALGO2, NCCL_ALLREDUCE_ALGO2::orig);
}

TEST_F(CvarTest, NCCL_ALLREDUCE_ALGO2_single_choice_1) {
  setenv("NCCL_ALLREDUCE_ALGO2", "dda", 1);
  ncclCvarInit();
  EXPECT_EQ(NCCL_ALLREDUCE_ALGO2, NCCL_ALLREDUCE_ALGO2::dda);
}

TEST_F(CvarTest, NCCL_ALLREDUCE_ALGO2_default_choice) {
  testDefaultValue("NCCL_ALLREDUCE_ALGO2");
  EXPECT_EQ(NCCL_ALLREDUCE_ALGO2, NCCL_ALLREDUCE_ALGO2::orig);
}

TEST_F(CvarTest, NCCL_DDA2_ALLREDUCE_TREE_THRESHOLD_NVS_value_0) {
  testIntValue("NCCL_DDA2_ALLREDUCE_TREE_THRESHOLD_NVS", -100);
  EXPECT_EQ(NCCL_DDA2_ALLREDUCE_TREE_THRESHOLD_NVS, -100);
}

TEST_F(CvarTest, NCCL_DDA2_ALLREDUCE_TREE_THRESHOLD_NVS_value_1) {
  testIntValue("NCCL_DDA2_ALLREDUCE_TREE_THRESHOLD_NVS", 0);
  EXPECT_EQ(NCCL_DDA2_ALLREDUCE_TREE_THRESHOLD_NVS, 0);
}

TEST_F(CvarTest, NCCL_DDA2_ALLREDUCE_TREE_THRESHOLD_NVS_value_2) {
  testIntValue("NCCL_DDA2_ALLREDUCE_TREE_THRESHOLD_NVS", 9999);
  EXPECT_EQ(NCCL_DDA2_ALLREDUCE_TREE_THRESHOLD_NVS, 9999);
}

TEST_F(CvarTest, NCCL_DDA2_ALLREDUCE_TREE_THRESHOLD_NVS_value_3) {
  testIntValue("NCCL_DDA2_ALLREDUCE_TREE_THRESHOLD_NVS", INT_MAX);
  EXPECT_EQ(NCCL_DDA2_ALLREDUCE_TREE_THRESHOLD_NVS, INT_MAX);
}

TEST_F(CvarTest, NCCL_DDA2_ALLREDUCE_TREE_THRESHOLD_NVS_value_4) {
  testIntValue("NCCL_DDA2_ALLREDUCE_TREE_THRESHOLD_NVS", INT_MIN);
  EXPECT_EQ(NCCL_DDA2_ALLREDUCE_TREE_THRESHOLD_NVS, INT_MIN);
}

TEST_F(CvarTest, NCCL_DDA2_ALLREDUCE_TREE_THRESHOLD_NVS_default_value) {
  testDefaultValue("NCCL_DDA2_ALLREDUCE_TREE_THRESHOLD_NVS");
  EXPECT_EQ(NCCL_DDA2_ALLREDUCE_TREE_THRESHOLD_NVS, 262144);
}

TEST_F(CvarTest, NCCL_DDA2_ALLREDUCE_TMPBUFF_SIZE_value_0) {
  testIntValue("NCCL_DDA2_ALLREDUCE_TMPBUFF_SIZE", -100);
  EXPECT_EQ(NCCL_DDA2_ALLREDUCE_TMPBUFF_SIZE, -100);
}

TEST_F(CvarTest, NCCL_DDA2_ALLREDUCE_TMPBUFF_SIZE_value_1) {
  testIntValue("NCCL_DDA2_ALLREDUCE_TMPBUFF_SIZE", 0);
  EXPECT_EQ(NCCL_DDA2_ALLREDUCE_TMPBUFF_SIZE, 0);
}

TEST_F(CvarTest, NCCL_DDA2_ALLREDUCE_TMPBUFF_SIZE_value_2) {
  testIntValue("NCCL_DDA2_ALLREDUCE_TMPBUFF_SIZE", 9999);
  EXPECT_EQ(NCCL_DDA2_ALLREDUCE_TMPBUFF_SIZE, 9999);
}

TEST_F(CvarTest, NCCL_DDA2_ALLREDUCE_TMPBUFF_SIZE_value_3) {
  testIntValue("NCCL_DDA2_ALLREDUCE_TMPBUFF_SIZE", INT_MAX);
  EXPECT_EQ(NCCL_DDA2_ALLREDUCE_TMPBUFF_SIZE, INT_MAX);
}

TEST_F(CvarTest, NCCL_DDA2_ALLREDUCE_TMPBUFF_SIZE_value_4) {
  testIntValue("NCCL_DDA2_ALLREDUCE_TMPBUFF_SIZE", INT_MIN);
  EXPECT_EQ(NCCL_DDA2_ALLREDUCE_TMPBUFF_SIZE, INT_MIN);
}

TEST_F(CvarTest, NCCL_DDA2_ALLREDUCE_TMPBUFF_SIZE_default_value) {
  testDefaultValue("NCCL_DDA2_ALLREDUCE_TMPBUFF_SIZE");
  EXPECT_EQ(NCCL_DDA2_ALLREDUCE_TMPBUFF_SIZE, 33554432);
}

TEST_F(CvarTest, NCCL_ALLGATHER_DIRECT_CUTOFF_value_0) {
  testIntValue("NCCL_ALLGATHER_DIRECT_CUTOFF", -100);
  EXPECT_EQ(NCCL_ALLGATHER_DIRECT_CUTOFF, -100);
}

TEST_F(CvarTest, NCCL_ALLGATHER_DIRECT_CUTOFF_value_1) {
  testIntValue("NCCL_ALLGATHER_DIRECT_CUTOFF", 0);
  EXPECT_EQ(NCCL_ALLGATHER_DIRECT_CUTOFF, 0);
}

TEST_F(CvarTest, NCCL_ALLGATHER_DIRECT_CUTOFF_value_2) {
  testIntValue("NCCL_ALLGATHER_DIRECT_CUTOFF", 9999);
  EXPECT_EQ(NCCL_ALLGATHER_DIRECT_CUTOFF, 9999);
}

TEST_F(CvarTest, NCCL_ALLGATHER_DIRECT_CUTOFF_value_3) {
  testIntValue("NCCL_ALLGATHER_DIRECT_CUTOFF", INT_MAX);
  EXPECT_EQ(NCCL_ALLGATHER_DIRECT_CUTOFF, INT_MAX);
}

TEST_F(CvarTest, NCCL_ALLGATHER_DIRECT_CUTOFF_value_4) {
  testIntValue("NCCL_ALLGATHER_DIRECT_CUTOFF", INT_MIN);
  EXPECT_EQ(NCCL_ALLGATHER_DIRECT_CUTOFF, INT_MIN);
}

TEST_F(CvarTest, NCCL_ALLGATHER_DIRECT_CUTOFF_default_value) {
  testDefaultValue("NCCL_ALLGATHER_DIRECT_CUTOFF");
  EXPECT_EQ(NCCL_ALLGATHER_DIRECT_CUTOFF, 524288);
}

TEST_F(CvarTest, NCCL_DDA_ALLREDUCE_MAX_BLOCKS_value_0) {
  testIntValue("NCCL_DDA_ALLREDUCE_MAX_BLOCKS", -100);
  EXPECT_EQ(NCCL_DDA_ALLREDUCE_MAX_BLOCKS, -100);
}

TEST_F(CvarTest, NCCL_DDA_ALLREDUCE_MAX_BLOCKS_value_1) {
  testIntValue("NCCL_DDA_ALLREDUCE_MAX_BLOCKS", 0);
  EXPECT_EQ(NCCL_DDA_ALLREDUCE_MAX_BLOCKS, 0);
}

TEST_F(CvarTest, NCCL_DDA_ALLREDUCE_MAX_BLOCKS_value_2) {
  testIntValue("NCCL_DDA_ALLREDUCE_MAX_BLOCKS", 9999);
  EXPECT_EQ(NCCL_DDA_ALLREDUCE_MAX_BLOCKS, 9999);
}

TEST_F(CvarTest, NCCL_DDA_ALLREDUCE_MAX_BLOCKS_value_3) {
  testIntValue("NCCL_DDA_ALLREDUCE_MAX_BLOCKS", INT_MAX);
  EXPECT_EQ(NCCL_DDA_ALLREDUCE_MAX_BLOCKS, INT_MAX);
}

TEST_F(CvarTest, NCCL_DDA_ALLREDUCE_MAX_BLOCKS_value_4) {
  testIntValue("NCCL_DDA_ALLREDUCE_MAX_BLOCKS", INT_MIN);
  EXPECT_EQ(NCCL_DDA_ALLREDUCE_MAX_BLOCKS, INT_MIN);
}

TEST_F(CvarTest, NCCL_DDA_ALLREDUCE_MAX_BLOCKS_default_value) {
  testDefaultValue("NCCL_DDA_ALLREDUCE_MAX_BLOCKS");
  EXPECT_EQ(NCCL_DDA_ALLREDUCE_MAX_BLOCKS, 1);
}

TEST_F(CvarTest, NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_NVS_value_0) {
  testIntValue("NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_NVS", -100);
  EXPECT_EQ(NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_NVS, -100);
}

TEST_F(CvarTest, NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_NVS_value_1) {
  testIntValue("NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_NVS", 0);
  EXPECT_EQ(NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_NVS, 0);
}

TEST_F(CvarTest, NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_NVS_value_2) {
  testIntValue("NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_NVS", 9999);
  EXPECT_EQ(NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_NVS, 9999);
}

TEST_F(CvarTest, NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_NVS_value_3) {
  testIntValue("NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_NVS", INT_MAX);
  EXPECT_EQ(NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_NVS, INT_MAX);
}

TEST_F(CvarTest, NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_NVS_value_4) {
  testIntValue("NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_NVS", INT_MIN);
  EXPECT_EQ(NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_NVS, INT_MIN);
}

TEST_F(CvarTest, NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_NVS_default_value) {
  testDefaultValue("NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_NVS");
  EXPECT_EQ(NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_NVS, 262144);
}

TEST_F(CvarTest, NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_HCM_value_0) {
  testIntValue("NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_HCM", -100);
  EXPECT_EQ(NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_HCM, -100);
}

TEST_F(CvarTest, NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_HCM_value_1) {
  testIntValue("NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_HCM", 0);
  EXPECT_EQ(NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_HCM, 0);
}

TEST_F(CvarTest, NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_HCM_value_2) {
  testIntValue("NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_HCM", 9999);
  EXPECT_EQ(NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_HCM, 9999);
}

TEST_F(CvarTest, NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_HCM_value_3) {
  testIntValue("NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_HCM", INT_MAX);
  EXPECT_EQ(NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_HCM, INT_MAX);
}

TEST_F(CvarTest, NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_HCM_value_4) {
  testIntValue("NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_HCM", INT_MIN);
  EXPECT_EQ(NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_HCM, INT_MIN);
}

TEST_F(CvarTest, NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_HCM_default_value) {
  testDefaultValue("NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_HCM");
  EXPECT_EQ(NCCL_DDA_ALLREDUCE_TREE_THRESHOLD_HCM, 65536);
}

TEST_F(CvarTest, NCCL_ALLREDUCE_SPARSE_BLOCK_NUM_THREAD_BLOCKS_value_0) {
  testIntValue("NCCL_ALLREDUCE_SPARSE_BLOCK_NUM_THREAD_BLOCKS", -100);
  EXPECT_EQ(NCCL_ALLREDUCE_SPARSE_BLOCK_NUM_THREAD_BLOCKS, -100);
}

TEST_F(CvarTest, NCCL_ALLREDUCE_SPARSE_BLOCK_NUM_THREAD_BLOCKS_value_1) {
  testIntValue("NCCL_ALLREDUCE_SPARSE_BLOCK_NUM_THREAD_BLOCKS", 0);
  EXPECT_EQ(NCCL_ALLREDUCE_SPARSE_BLOCK_NUM_THREAD_BLOCKS, 0);
}

TEST_F(CvarTest, NCCL_ALLREDUCE_SPARSE_BLOCK_NUM_THREAD_BLOCKS_value_2) {
  testIntValue("NCCL_ALLREDUCE_SPARSE_BLOCK_NUM_THREAD_BLOCKS", 9999);
  EXPECT_EQ(NCCL_ALLREDUCE_SPARSE_BLOCK_NUM_THREAD_BLOCKS, 9999);
}

TEST_F(CvarTest, NCCL_ALLREDUCE_SPARSE_BLOCK_NUM_THREAD_BLOCKS_value_3) {
  testIntValue("NCCL_ALLREDUCE_SPARSE_BLOCK_NUM_THREAD_BLOCKS", INT_MAX);
  EXPECT_EQ(NCCL_ALLREDUCE_SPARSE_BLOCK_NUM_THREAD_BLOCKS, INT_MAX);
}

TEST_F(CvarTest, NCCL_ALLREDUCE_SPARSE_BLOCK_NUM_THREAD_BLOCKS_value_4) {
  testIntValue("NCCL_ALLREDUCE_SPARSE_BLOCK_NUM_THREAD_BLOCKS", INT_MIN);
  EXPECT_EQ(NCCL_ALLREDUCE_SPARSE_BLOCK_NUM_THREAD_BLOCKS, INT_MIN);
}

TEST_F(CvarTest, NCCL_ALLREDUCE_SPARSE_BLOCK_NUM_THREAD_BLOCKS_default_value) {
  testDefaultValue("NCCL_ALLREDUCE_SPARSE_BLOCK_NUM_THREAD_BLOCKS");
  EXPECT_EQ(NCCL_ALLREDUCE_SPARSE_BLOCK_NUM_THREAD_BLOCKS, -1);
}

TEST_F(CvarTest, NCCL_ALLREDUCE_SPARSE_BLOCK_THREAD_BLOCK_SIZE_value_0) {
  testIntValue("NCCL_ALLREDUCE_SPARSE_BLOCK_THREAD_BLOCK_SIZE", -100);
  EXPECT_EQ(NCCL_ALLREDUCE_SPARSE_BLOCK_THREAD_BLOCK_SIZE, -100);
}

TEST_F(CvarTest, NCCL_ALLREDUCE_SPARSE_BLOCK_THREAD_BLOCK_SIZE_value_1) {
  testIntValue("NCCL_ALLREDUCE_SPARSE_BLOCK_THREAD_BLOCK_SIZE", 0);
  EXPECT_EQ(NCCL_ALLREDUCE_SPARSE_BLOCK_THREAD_BLOCK_SIZE, 0);
}

TEST_F(CvarTest, NCCL_ALLREDUCE_SPARSE_BLOCK_THREAD_BLOCK_SIZE_value_2) {
  testIntValue("NCCL_ALLREDUCE_SPARSE_BLOCK_THREAD_BLOCK_SIZE", 9999);
  EXPECT_EQ(NCCL_ALLREDUCE_SPARSE_BLOCK_THREAD_BLOCK_SIZE, 9999);
}

TEST_F(CvarTest, NCCL_ALLREDUCE_SPARSE_BLOCK_THREAD_BLOCK_SIZE_value_3) {
  testIntValue("NCCL_ALLREDUCE_SPARSE_BLOCK_THREAD_BLOCK_SIZE", INT_MAX);
  EXPECT_EQ(NCCL_ALLREDUCE_SPARSE_BLOCK_THREAD_BLOCK_SIZE, INT_MAX);
}

TEST_F(CvarTest, NCCL_ALLREDUCE_SPARSE_BLOCK_THREAD_BLOCK_SIZE_value_4) {
  testIntValue("NCCL_ALLREDUCE_SPARSE_BLOCK_THREAD_BLOCK_SIZE", INT_MIN);
  EXPECT_EQ(NCCL_ALLREDUCE_SPARSE_BLOCK_THREAD_BLOCK_SIZE, INT_MIN);
}

TEST_F(CvarTest, NCCL_ALLREDUCE_SPARSE_BLOCK_THREAD_BLOCK_SIZE_default_value) {
  testDefaultValue("NCCL_ALLREDUCE_SPARSE_BLOCK_THREAD_BLOCK_SIZE");
  EXPECT_EQ(NCCL_ALLREDUCE_SPARSE_BLOCK_THREAD_BLOCK_SIZE, -1);
}

TEST_F(CvarTest, NCCL_DDA_FORCE_P2P_ACCESS_value_y0) {
  setenv("NCCL_DDA_FORCE_P2P_ACCESS", "y", 1);
  ncclCvarInit();
  EXPECT_TRUE(NCCL_DDA_FORCE_P2P_ACCESS);
}

TEST_F(CvarTest, NCCL_DDA_FORCE_P2P_ACCESS_value_y1) {
  setenv("NCCL_DDA_FORCE_P2P_ACCESS", "yes", 1);
  ncclCvarInit();
  EXPECT_TRUE(NCCL_DDA_FORCE_P2P_ACCESS);
}

TEST_F(CvarTest, NCCL_DDA_FORCE_P2P_ACCESS_value_y2) {
  setenv("NCCL_DDA_FORCE_P2P_ACCESS", "true", 1);
  ncclCvarInit();
  EXPECT_TRUE(NCCL_DDA_FORCE_P2P_ACCESS);
}

TEST_F(CvarTest, NCCL_DDA_FORCE_P2P_ACCESS_value_y3) {
  setenv("NCCL_DDA_FORCE_P2P_ACCESS", "1", 1);
  ncclCvarInit();
  EXPECT_TRUE(NCCL_DDA_FORCE_P2P_ACCESS);
}

TEST_F(CvarTest, NCCL_DDA_FORCE_P2P_ACCESS_value_n0) {
  setenv("NCCL_DDA_FORCE_P2P_ACCESS", "n", 1);
  ncclCvarInit();
  EXPECT_FALSE(NCCL_DDA_FORCE_P2P_ACCESS);
}

TEST_F(CvarTest, NCCL_DDA_FORCE_P2P_ACCESS_value_n1) {
  setenv("NCCL_DDA_FORCE_P2P_ACCESS", "no", 1);
  ncclCvarInit();
  EXPECT_FALSE(NCCL_DDA_FORCE_P2P_ACCESS);
}

TEST_F(CvarTest, NCCL_DDA_FORCE_P2P_ACCESS_value_n2) {
  setenv("NCCL_DDA_FORCE_P2P_ACCESS", "false", 1);
  ncclCvarInit();
  EXPECT_FALSE(NCCL_DDA_FORCE_P2P_ACCESS);
}

TEST_F(CvarTest, NCCL_DDA_FORCE_P2P_ACCESS_value_n3) {
  setenv("NCCL_DDA_FORCE_P2P_ACCESS", "0", 1);
  ncclCvarInit();
  EXPECT_FALSE(NCCL_DDA_FORCE_P2P_ACCESS);
}

TEST_F(CvarTest, NCCL_SENDRECV_ALGO_single_choice_0) {
  setenv("NCCL_SENDRECV_ALGO", "orig", 1);
  ncclCvarInit();
  EXPECT_EQ(NCCL_SENDRECV_ALGO, NCCL_SENDRECV_ALGO::orig);
}

TEST_F(CvarTest, NCCL_SENDRECV_ALGO_single_choice_1) {
  setenv("NCCL_SENDRECV_ALGO", "ctran", 1);
  ncclCvarInit();
  EXPECT_EQ(NCCL_SENDRECV_ALGO, NCCL_SENDRECV_ALGO::ctran);
}

TEST_F(CvarTest, NCCL_SENDRECV_ALGO_default_choice) {
  testDefaultValue("NCCL_SENDRECV_ALGO");
  EXPECT_EQ(NCCL_SENDRECV_ALGO, NCCL_SENDRECV_ALGO::orig);
}

TEST_F(CvarTest, NCCL_ALLGATHER_ALGO_single_choice_0) {
  setenv("NCCL_ALLGATHER_ALGO", "orig", 1);
  ncclCvarInit();
  EXPECT_EQ(NCCL_ALLGATHER_ALGO, NCCL_ALLGATHER_ALGO::orig);
}

TEST_F(CvarTest, NCCL_ALLGATHER_ALGO_single_choice_1) {
  setenv("NCCL_ALLGATHER_ALGO", "ctdirect", 1);
  ncclCvarInit();
  EXPECT_EQ(NCCL_ALLGATHER_ALGO, NCCL_ALLGATHER_ALGO::ctdirect);
}

TEST_F(CvarTest, NCCL_ALLGATHER_ALGO_single_choice_2) {
  setenv("NCCL_ALLGATHER_ALGO", "ctring", 1);
  ncclCvarInit();
  EXPECT_EQ(NCCL_ALLGATHER_ALGO, NCCL_ALLGATHER_ALGO::ctring);
}

TEST_F(CvarTest, NCCL_ALLGATHER_ALGO_single_choice_3) {
  setenv("NCCL_ALLGATHER_ALGO", "ctrd", 1);
  ncclCvarInit();
  EXPECT_EQ(NCCL_ALLGATHER_ALGO, NCCL_ALLGATHER_ALGO::ctrd);
}

TEST_F(CvarTest, NCCL_ALLGATHER_ALGO_default_choice) {
  testDefaultValue("NCCL_ALLGATHER_ALGO");
  EXPECT_EQ(NCCL_ALLGATHER_ALGO, NCCL_ALLGATHER_ALGO::orig);
}

TEST_F(CvarTest, NCCL_IB_HCA_valuelist_0) {
  setenv("NCCL_IB_HCA", "val1,val2,val3", 1);
  std::vector<std::string> vals{"val1","val2","val3"};
  ncclCvarInit();
  checkListValues<std::string>(vals, NCCL_IB_HCA);
}

TEST_F(CvarTest, NCCL_IB_HCA_valuelist_1) {
  setenv("NCCL_IB_HCA", "val1:1,val2:2,val3:3", 1);
  std::vector<std::string> vals{"val1:1","val2:2","val3:3"};
  ncclCvarInit();
  checkListValues<std::string>(vals, NCCL_IB_HCA);
}

TEST_F(CvarTest, NCCL_IB_HCA_valuelist_2) {
  setenv("NCCL_IB_HCA", "val", 1);
  std::vector<std::string> vals{"val"};
  ncclCvarInit();
  checkListValues<std::string>(vals, NCCL_IB_HCA);
}

TEST_F(CvarTest, NCCL_IB_HCA_valuelist_3) {
  setenv("NCCL_IB_HCA", "val1, val_w_space  ", 1);
  std::vector<std::string> vals{"val1","val_w_space"};
  ncclCvarInit();
  checkListValues<std::string>(vals, NCCL_IB_HCA);
}

TEST_F(CvarTest, NCCL_IB_HCA_default_value) {
  testDefaultValue("NCCL_IB_HCA");
  EXPECT_EQ(NCCL_IB_HCA.size(), 0);
}

TEST_F(CvarTest, NCCL_IB_HCA_prefix_0) {
  setenv("NCCL_IB_HCA", "^val1,val2,val3", 1);
  std::vector<std::string> vals{"val1","val2","val3"};
  ncclCvarInit();
  EXPECT_EQ(NCCL_IB_HCA_PREFIX, "^");
  checkListValues<std::string>(vals, NCCL_IB_HCA);
}

TEST_F(CvarTest, NCCL_IB_HCA_prefix_1) {
  setenv("NCCL_IB_HCA", "=val1,val2,val3", 1);
  std::vector<std::string> vals{"val1","val2","val3"};
  ncclCvarInit();
  EXPECT_EQ(NCCL_IB_HCA_PREFIX, "=");
  checkListValues<std::string>(vals, NCCL_IB_HCA);
}

TEST_F(CvarTest, NCCL_IB_HCA_prefix_2) {
  setenv("NCCL_IB_HCA", "val1,val2,val3", 1);
  std::vector<std::string> vals{"val1","val2","val3"};
  ncclCvarInit();
  EXPECT_EQ(NCCL_IB_HCA_PREFIX, "");
  checkListValues<std::string>(vals, NCCL_IB_HCA);
}

TEST_F(CvarTest, NCCL_CTRAN_IB_TRAFFIC_PROFILNG_value_y0) {
  setenv("NCCL_CTRAN_IB_TRAFFIC_PROFILNG", "y", 1);
  ncclCvarInit();
  EXPECT_TRUE(NCCL_CTRAN_IB_TRAFFIC_PROFILNG);
}

TEST_F(CvarTest, NCCL_CTRAN_IB_TRAFFIC_PROFILNG_value_y1) {
  setenv("NCCL_CTRAN_IB_TRAFFIC_PROFILNG", "yes", 1);
  ncclCvarInit();
  EXPECT_TRUE(NCCL_CTRAN_IB_TRAFFIC_PROFILNG);
}

TEST_F(CvarTest, NCCL_CTRAN_IB_TRAFFIC_PROFILNG_value_y2) {
  setenv("NCCL_CTRAN_IB_TRAFFIC_PROFILNG", "true", 1);
  ncclCvarInit();
  EXPECT_TRUE(NCCL_CTRAN_IB_TRAFFIC_PROFILNG);
}

TEST_F(CvarTest, NCCL_CTRAN_IB_TRAFFIC_PROFILNG_value_y3) {
  setenv("NCCL_CTRAN_IB_TRAFFIC_PROFILNG", "1", 1);
  ncclCvarInit();
  EXPECT_TRUE(NCCL_CTRAN_IB_TRAFFIC_PROFILNG);
}

TEST_F(CvarTest, NCCL_CTRAN_IB_TRAFFIC_PROFILNG_value_n0) {
  setenv("NCCL_CTRAN_IB_TRAFFIC_PROFILNG", "n", 1);
  ncclCvarInit();
  EXPECT_FALSE(NCCL_CTRAN_IB_TRAFFIC_PROFILNG);
}

TEST_F(CvarTest, NCCL_CTRAN_IB_TRAFFIC_PROFILNG_value_n1) {
  setenv("NCCL_CTRAN_IB_TRAFFIC_PROFILNG", "no", 1);
  ncclCvarInit();
  EXPECT_FALSE(NCCL_CTRAN_IB_TRAFFIC_PROFILNG);
}

TEST_F(CvarTest, NCCL_CTRAN_IB_TRAFFIC_PROFILNG_value_n2) {
  setenv("NCCL_CTRAN_IB_TRAFFIC_PROFILNG", "false", 1);
  ncclCvarInit();
  EXPECT_FALSE(NCCL_CTRAN_IB_TRAFFIC_PROFILNG);
}

TEST_F(CvarTest, NCCL_CTRAN_IB_TRAFFIC_PROFILNG_value_n3) {
  setenv("NCCL_CTRAN_IB_TRAFFIC_PROFILNG", "0", 1);
  ncclCvarInit();
  EXPECT_FALSE(NCCL_CTRAN_IB_TRAFFIC_PROFILNG);
}

TEST_F(CvarTest, NCCL_CTRAN_IB_MAX_QPS_value_0) {
  testIntValue("NCCL_CTRAN_IB_MAX_QPS", -100);
  EXPECT_EQ(NCCL_CTRAN_IB_MAX_QPS, -100);
}

TEST_F(CvarTest, NCCL_CTRAN_IB_MAX_QPS_value_1) {
  testIntValue("NCCL_CTRAN_IB_MAX_QPS", 0);
  EXPECT_EQ(NCCL_CTRAN_IB_MAX_QPS, 0);
}

TEST_F(CvarTest, NCCL_CTRAN_IB_MAX_QPS_value_2) {
  testIntValue("NCCL_CTRAN_IB_MAX_QPS", 9999);
  EXPECT_EQ(NCCL_CTRAN_IB_MAX_QPS, 9999);
}

TEST_F(CvarTest, NCCL_CTRAN_IB_MAX_QPS_value_3) {
  testIntValue("NCCL_CTRAN_IB_MAX_QPS", INT_MAX);
  EXPECT_EQ(NCCL_CTRAN_IB_MAX_QPS, INT_MAX);
}

TEST_F(CvarTest, NCCL_CTRAN_IB_MAX_QPS_value_4) {
  testIntValue("NCCL_CTRAN_IB_MAX_QPS", INT_MIN);
  EXPECT_EQ(NCCL_CTRAN_IB_MAX_QPS, INT_MIN);
}

TEST_F(CvarTest, NCCL_CTRAN_IB_MAX_QPS_default_value) {
  testDefaultValue("NCCL_CTRAN_IB_MAX_QPS");
  EXPECT_EQ(NCCL_CTRAN_IB_MAX_QPS, 1);
}

TEST_F(CvarTest, NCCL_CTRAN_IB_QP_SCALING_THRESHOLD_value_0) {
  testIntValue("NCCL_CTRAN_IB_QP_SCALING_THRESHOLD", -100);
  EXPECT_EQ(NCCL_CTRAN_IB_QP_SCALING_THRESHOLD, -100);
}

TEST_F(CvarTest, NCCL_CTRAN_IB_QP_SCALING_THRESHOLD_value_1) {
  testIntValue("NCCL_CTRAN_IB_QP_SCALING_THRESHOLD", 0);
  EXPECT_EQ(NCCL_CTRAN_IB_QP_SCALING_THRESHOLD, 0);
}

TEST_F(CvarTest, NCCL_CTRAN_IB_QP_SCALING_THRESHOLD_value_2) {
  testIntValue("NCCL_CTRAN_IB_QP_SCALING_THRESHOLD", 9999);
  EXPECT_EQ(NCCL_CTRAN_IB_QP_SCALING_THRESHOLD, 9999);
}

TEST_F(CvarTest, NCCL_CTRAN_IB_QP_SCALING_THRESHOLD_value_3) {
  testIntValue("NCCL_CTRAN_IB_QP_SCALING_THRESHOLD", INT_MAX);
  EXPECT_EQ(NCCL_CTRAN_IB_QP_SCALING_THRESHOLD, INT_MAX);
}

TEST_F(CvarTest, NCCL_CTRAN_IB_QP_SCALING_THRESHOLD_value_4) {
  testIntValue("NCCL_CTRAN_IB_QP_SCALING_THRESHOLD", INT_MIN);
  EXPECT_EQ(NCCL_CTRAN_IB_QP_SCALING_THRESHOLD, INT_MIN);
}

TEST_F(CvarTest, NCCL_CTRAN_IB_QP_SCALING_THRESHOLD_default_value) {
  testDefaultValue("NCCL_CTRAN_IB_QP_SCALING_THRESHOLD");
  EXPECT_EQ(NCCL_CTRAN_IB_QP_SCALING_THRESHOLD, 1048576);
}

TEST_F(CvarTest, NCCL_CTRAN_PROFILING_single_choice_0) {
  setenv("NCCL_CTRAN_PROFILING", "none", 1);
  ncclCvarInit();
  EXPECT_EQ(NCCL_CTRAN_PROFILING, NCCL_CTRAN_PROFILING::none);
}

TEST_F(CvarTest, NCCL_CTRAN_PROFILING_single_choice_1) {
  setenv("NCCL_CTRAN_PROFILING", "stdout", 1);
  ncclCvarInit();
  EXPECT_EQ(NCCL_CTRAN_PROFILING, NCCL_CTRAN_PROFILING::stdout);
}

TEST_F(CvarTest, NCCL_CTRAN_PROFILING_single_choice_2) {
  setenv("NCCL_CTRAN_PROFILING", "info", 1);
  ncclCvarInit();
  EXPECT_EQ(NCCL_CTRAN_PROFILING, NCCL_CTRAN_PROFILING::info);
}

TEST_F(CvarTest, NCCL_CTRAN_PROFILING_single_choice_3) {
  setenv("NCCL_CTRAN_PROFILING", "kineto", 1);
  ncclCvarInit();
  EXPECT_EQ(NCCL_CTRAN_PROFILING, NCCL_CTRAN_PROFILING::kineto);
}

TEST_F(CvarTest, NCCL_CTRAN_PROFILING_default_choice) {
  testDefaultValue("NCCL_CTRAN_PROFILING");
  EXPECT_EQ(NCCL_CTRAN_PROFILING, NCCL_CTRAN_PROFILING::none);
}

TEST_F(CvarTest, NCCL_CTRAN_KINETO_PROFILE_DIR_value_0) {
  setenv("NCCL_CTRAN_KINETO_PROFILE_DIR", "val1", 1);
  ncclCvarInit();
  EXPECT_EQ(NCCL_CTRAN_KINETO_PROFILE_DIR, "val1");
}

TEST_F(CvarTest, NCCL_CTRAN_KINETO_PROFILE_DIR_value_1) {
  setenv("NCCL_CTRAN_KINETO_PROFILE_DIR", "  val2_with_space   ", 1);
  ncclCvarInit();
  EXPECT_EQ(NCCL_CTRAN_KINETO_PROFILE_DIR, "val2_with_space");
}

TEST_F(CvarTest, NCCL_CTRAN_KINETO_PROFILE_DIR_default_value) {
  testDefaultValue("NCCL_CTRAN_KINETO_PROFILE_DIR");
  EXPECT_EQ(NCCL_CTRAN_KINETO_PROFILE_DIR, "/tmp");
}

TEST_F(CvarTest, NCCL_CTRAN_REGISTER_single_choice_0) {
  setenv("NCCL_CTRAN_REGISTER", "none", 1);
  ncclCvarInit();
  EXPECT_EQ(NCCL_CTRAN_REGISTER, NCCL_CTRAN_REGISTER::none);
}

TEST_F(CvarTest, NCCL_CTRAN_REGISTER_single_choice_1) {
  setenv("NCCL_CTRAN_REGISTER", "lazy", 1);
  ncclCvarInit();
  EXPECT_EQ(NCCL_CTRAN_REGISTER, NCCL_CTRAN_REGISTER::lazy);
}

TEST_F(CvarTest, NCCL_CTRAN_REGISTER_single_choice_2) {
  setenv("NCCL_CTRAN_REGISTER", "eager", 1);
  ncclCvarInit();
  EXPECT_EQ(NCCL_CTRAN_REGISTER, NCCL_CTRAN_REGISTER::eager);
}

TEST_F(CvarTest, NCCL_CTRAN_REGISTER_default_choice) {
  testDefaultValue("NCCL_CTRAN_REGISTER");
  EXPECT_EQ(NCCL_CTRAN_REGISTER, NCCL_CTRAN_REGISTER::lazy);
}

TEST_F(CvarTest, NCCL_CTRAN_BACKENDS_single_choice_0) {
  setenv("NCCL_CTRAN_BACKENDS", "ib", 1);
  ncclCvarInit();
  std::vector<enum NCCL_CTRAN_BACKENDS> vals{NCCL_CTRAN_BACKENDS::ib};
  checkListValues<enum NCCL_CTRAN_BACKENDS>(vals, NCCL_CTRAN_BACKENDS);
}

TEST_F(CvarTest, NCCL_CTRAN_BACKENDS_all_choices) {
  setenv("NCCL_CTRAN_BACKENDS", "ib", 1);
  ncclCvarInit();
  std::vector<enum NCCL_CTRAN_BACKENDS> vals{NCCL_CTRAN_BACKENDS::ib};
  checkListValues<enum NCCL_CTRAN_BACKENDS>(vals, NCCL_CTRAN_BACKENDS);
}

TEST_F(CvarTest, NCCL_CTRAN_BACKENDS_default_choices) {
  testDefaultValue("NCCL_CTRAN_BACKENDS");
  std::vector<enum NCCL_CTRAN_BACKENDS> vals{NCCL_CTRAN_BACKENDS::ib};
  checkListValues<enum NCCL_CTRAN_BACKENDS>(vals, NCCL_CTRAN_BACKENDS);
}

TEST_F(CvarTest, NCCL_CTRAN_REGISTER_REPORT_SNAPSHOT_COUNT_value_0) {
  testIntValue("NCCL_CTRAN_REGISTER_REPORT_SNAPSHOT_COUNT", -100);
  EXPECT_EQ(NCCL_CTRAN_REGISTER_REPORT_SNAPSHOT_COUNT, -100);
}

TEST_F(CvarTest, NCCL_CTRAN_REGISTER_REPORT_SNAPSHOT_COUNT_value_1) {
  testIntValue("NCCL_CTRAN_REGISTER_REPORT_SNAPSHOT_COUNT", 0);
  EXPECT_EQ(NCCL_CTRAN_REGISTER_REPORT_SNAPSHOT_COUNT, 0);
}

TEST_F(CvarTest, NCCL_CTRAN_REGISTER_REPORT_SNAPSHOT_COUNT_value_2) {
  testIntValue("NCCL_CTRAN_REGISTER_REPORT_SNAPSHOT_COUNT", 9999);
  EXPECT_EQ(NCCL_CTRAN_REGISTER_REPORT_SNAPSHOT_COUNT, 9999);
}

TEST_F(CvarTest, NCCL_CTRAN_REGISTER_REPORT_SNAPSHOT_COUNT_value_3) {
  testIntValue("NCCL_CTRAN_REGISTER_REPORT_SNAPSHOT_COUNT", INT_MAX);
  EXPECT_EQ(NCCL_CTRAN_REGISTER_REPORT_SNAPSHOT_COUNT, INT_MAX);
}

TEST_F(CvarTest, NCCL_CTRAN_REGISTER_REPORT_SNAPSHOT_COUNT_value_4) {
  testIntValue("NCCL_CTRAN_REGISTER_REPORT_SNAPSHOT_COUNT", INT_MIN);
  EXPECT_EQ(NCCL_CTRAN_REGISTER_REPORT_SNAPSHOT_COUNT, INT_MIN);
}

TEST_F(CvarTest, NCCL_CTRAN_REGISTER_REPORT_SNAPSHOT_COUNT_default_value) {
  testDefaultValue("NCCL_CTRAN_REGISTER_REPORT_SNAPSHOT_COUNT");
  EXPECT_EQ(NCCL_CTRAN_REGISTER_REPORT_SNAPSHOT_COUNT, -1);
}

TEST_F(CvarTest, NCCL_CTRAN_PROFILING_REPORT_COUNT_value_0) {
  testIntValue("NCCL_CTRAN_PROFILING_REPORT_COUNT", -100);
  EXPECT_EQ(NCCL_CTRAN_PROFILING_REPORT_COUNT, -100);
}

TEST_F(CvarTest, NCCL_CTRAN_PROFILING_REPORT_COUNT_value_1) {
  testIntValue("NCCL_CTRAN_PROFILING_REPORT_COUNT", 0);
  EXPECT_EQ(NCCL_CTRAN_PROFILING_REPORT_COUNT, 0);
}

TEST_F(CvarTest, NCCL_CTRAN_PROFILING_REPORT_COUNT_value_2) {
  testIntValue("NCCL_CTRAN_PROFILING_REPORT_COUNT", 9999);
  EXPECT_EQ(NCCL_CTRAN_PROFILING_REPORT_COUNT, 9999);
}

TEST_F(CvarTest, NCCL_CTRAN_PROFILING_REPORT_COUNT_value_3) {
  testIntValue("NCCL_CTRAN_PROFILING_REPORT_COUNT", INT_MAX);
  EXPECT_EQ(NCCL_CTRAN_PROFILING_REPORT_COUNT, INT_MAX);
}

TEST_F(CvarTest, NCCL_CTRAN_PROFILING_REPORT_COUNT_value_4) {
  testIntValue("NCCL_CTRAN_PROFILING_REPORT_COUNT", INT_MIN);
  EXPECT_EQ(NCCL_CTRAN_PROFILING_REPORT_COUNT, INT_MIN);
}

TEST_F(CvarTest, NCCL_CTRAN_PROFILING_REPORT_COUNT_default_value) {
  testDefaultValue("NCCL_CTRAN_PROFILING_REPORT_COUNT");
  EXPECT_EQ(NCCL_CTRAN_PROFILING_REPORT_COUNT, 100);
}



/**
* END of generated tests
*/

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::AddGlobalTestEnvironment(new NCCLEnvironment);
  return RUN_ALL_TESTS();
}
