#include <gtest/gtest.h>
#include "SimModel/SolverWarning.h"

using namespace SimModelNative;

TEST(SolverWarningTest, TwoArgConstructor_StoresTimeAndMessage)
{
   SolverWarning warning(1.5, "Step size too small");
   EXPECT_DOUBLE_EQ(1.5, warning.Time());
   EXPECT_EQ("Step size too small", warning.Message());
}

TEST(SolverWarningTest, OneArgConstructor_SetsTimeToZero)
{
   SolverWarning warning("General warning");
   EXPECT_DOUBLE_EQ(0.0, warning.Time());
   EXPECT_EQ("General warning", warning.Message());
}

TEST(SolverWarningTest, TwoArgConstructor_ZeroTime)
{
   SolverWarning warning(0.0, "At time zero");
   EXPECT_DOUBLE_EQ(0.0, warning.Time());
   EXPECT_EQ("At time zero", warning.Message());
}

TEST(SolverWarningTest, TwoArgConstructor_LargeTime)
{
   SolverWarning warning(1e10, "Late warning");
   EXPECT_DOUBLE_EQ(1e10, warning.Time());
}

TEST(SolverWarningTest, OneArgConstructor_EmptyMessage)
{
   SolverWarning warning("");
   EXPECT_EQ("", warning.Message());
   EXPECT_DOUBLE_EQ(0.0, warning.Time());
}
