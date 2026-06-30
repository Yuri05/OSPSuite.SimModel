#include <gtest/gtest.h>
#include "SimModel/SolverWarning.h"

using namespace SimModelNative;

TEST(when_creating_a_solver_warning_with_time_and_message, should_store_both_values)
{
   SolverWarning warning(1.5, "Step size too small");
   EXPECT_DOUBLE_EQ(1.5, warning.Time());
   EXPECT_EQ("Step size too small", warning.Message());
}

TEST(when_creating_a_solver_warning_with_message_only, should_set_time_to_zero)
{
   SolverWarning warning("General warning");
   EXPECT_DOUBLE_EQ(0.0, warning.Time());
   EXPECT_EQ("General warning", warning.Message());
}

TEST(when_creating_a_solver_warning_with_zero_time, should_store_zero_time_and_the_message)
{
   SolverWarning warning(0.0, "At time zero");
   EXPECT_DOUBLE_EQ(0.0, warning.Time());
   EXPECT_EQ("At time zero", warning.Message());
}

TEST(when_creating_a_solver_warning_with_large_time_value, should_store_the_large_time)
{
   SolverWarning warning(1e10, "Late warning");
   EXPECT_DOUBLE_EQ(1e10, warning.Time());
}

TEST(when_creating_a_solver_warning_with_empty_message, should_store_empty_message_and_zero_time)
{
   SolverWarning warning("");
   EXPECT_EQ("", warning.Message());
   EXPECT_DOUBLE_EQ(0.0, warning.Time());
}
