#include <gtest/gtest.h>
#include "SimModel/Rcm.h"
#include <ErrorData.h>
#include <set>

using namespace SimModelNative;

class when_testing_rcm : public ::testing::Test
{
protected:
   Rcm rcm;

   std::vector<std::vector<bool>> createMatrix(int n) const
   {
      return std::vector<std::vector<bool>>(n, std::vector<bool>(n, false));
   }

   void verifyPermutation(const std::vector<unsigned int>& perm, unsigned int n) const
   {
      ASSERT_EQ(n, perm.size());
      std::set<unsigned int> seen;
      for (auto idx : perm)
      {
         EXPECT_LT(idx, n);
         seen.insert(idx);
      }
      EXPECT_EQ(n, seen.size());
   }
};

TEST_F(when_testing_rcm, should_return_empty_permutation_for_empty_matrix)
{
   auto matrix = createMatrix(0);
   auto perm = rcm.GenRcm(matrix);
   EXPECT_TRUE(perm.empty());
}

TEST_F(when_testing_rcm, should_return_trivial_permutation_for_single_node)
{
   auto matrix = createMatrix(1);
   auto perm = rcm.GenRcm(matrix);

   ASSERT_EQ(1u, perm.size());
   EXPECT_EQ(0u, perm[0]);
}

TEST_F(when_testing_rcm, should_return_valid_permutation_for_two_disconnected_nodes)
{
   auto matrix = createMatrix(2);
   auto perm = rcm.GenRcm(matrix);
   verifyPermutation(perm, 2);
}

TEST_F(when_testing_rcm, should_return_valid_permutation_for_two_connected_nodes)
{
   auto matrix = createMatrix(2);
   matrix[0][1] = true;
   matrix[1][0] = true;

   auto perm = rcm.GenRcm(matrix);
   verifyPermutation(perm, 2);
}

TEST_F(when_testing_rcm, should_return_valid_permutation_for_line_graph)
{
   // 0 -- 1 -- 2 -- 3
   auto matrix = createMatrix(4);
   matrix[0][1] = true; matrix[1][0] = true;
   matrix[1][2] = true; matrix[2][1] = true;
   matrix[2][3] = true; matrix[3][2] = true;

   auto perm = rcm.GenRcm(matrix);
   verifyPermutation(perm, 4);
}

TEST_F(when_testing_rcm, should_return_valid_permutation_for_ten_node_example)
{
   // The 10x10 example from the header documentation
   auto matrix = createMatrix(10);

   // Row 0: connected to 3, 5
   matrix[0][3] = true; matrix[0][5] = true;
   // Row 1: connected to 2, 4, 6, 9
   matrix[1][2] = true; matrix[1][4] = true; matrix[1][6] = true; matrix[1][9] = true;
   // Row 2: connected to 1, 3, 4
   matrix[2][1] = true; matrix[2][3] = true; matrix[2][4] = true;
   // Row 3: connected to 0, 2, 5, 8
   matrix[3][0] = true; matrix[3][2] = true; matrix[3][5] = true; matrix[3][8] = true;
   // Row 4: connected to 1, 2, 6
   matrix[4][1] = true; matrix[4][2] = true; matrix[4][6] = true;
   // Row 5: connected to 0, 3, 6, 7
   matrix[5][0] = true; matrix[5][3] = true; matrix[5][6] = true; matrix[5][7] = true;
   // Row 6: connected to 1, 4, 5, 7
   matrix[6][1] = true; matrix[6][4] = true; matrix[6][5] = true; matrix[6][7] = true;
   // Row 7: connected to 5, 6
   matrix[7][5] = true; matrix[7][6] = true;
   // Row 8: connected to 3
   matrix[8][3] = true;
   // Row 9: connected to 1
   matrix[9][1] = true;

   auto perm = rcm.GenRcm(matrix);
   verifyPermutation(perm, 10);
}

TEST_F(when_testing_rcm, should_handle_directed_graph_by_making_it_symmetric)
{
   // Provide a directed (non-symmetric) adjacency and verify GenRcm handles it
   auto matrix = createMatrix(3);
   matrix[0][1] = true;  // 0->1 only (not symmetric)
   matrix[1][2] = true;  // 1->2 only

   auto perm = rcm.GenRcm(matrix);
   verifyPermutation(perm, 3);
}

TEST_F(when_testing_rcm, should_return_valid_permutation_for_complete_graph)
{
   auto matrix = createMatrix(4);
   for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
         if (i != j)
            matrix[i][j] = true;

   auto perm = rcm.GenRcm(matrix);
   verifyPermutation(perm, 4);
}

TEST_F(when_testing_rcm, should_return_valid_permutation_for_star_graph)
{
   // Node 0 connected to all others; others not connected to each other
   auto matrix = createMatrix(5);
   for (int i = 1; i < 5; i++)
   {
      matrix[0][i] = true;
      matrix[i][0] = true;
   }

   auto perm = rcm.GenRcm(matrix);
   verifyPermutation(perm, 5);
}
