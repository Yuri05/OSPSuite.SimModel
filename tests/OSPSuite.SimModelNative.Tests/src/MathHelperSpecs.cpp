#include <gtest/gtest.h>
#include "SimModel/MathHelper.h"
#include <ErrorData.h>

using namespace SimModelNative;

TEST(when_getting_nan_value, should_return_a_nan)
{
   double nan = MathHelper::GetNaN();
   EXPECT_TRUE(MathHelper::IsNaN(nan));
}

TEST(when_checking_is_nan_for_regular_values, should_return_false)
{
   EXPECT_FALSE(MathHelper::IsNaN(0.0));
   EXPECT_FALSE(MathHelper::IsNaN(1.0));
   EXPECT_FALSE(MathHelper::IsNaN(-1.0));
   EXPECT_FALSE(MathHelper::IsNaN(1e300));
}

TEST(when_checking_is_nan_for_infinity_values, should_return_false)
{
   EXPECT_FALSE(MathHelper::IsNaN(MathHelper::GetInf()));
   EXPECT_FALSE(MathHelper::IsNaN(MathHelper::GetNegInf()));
}

TEST(when_getting_positive_infinity, should_return_positive_infinity)
{
   double inf = MathHelper::GetInf();
   EXPECT_TRUE(MathHelper::IsInf(inf));
   EXPECT_FALSE(MathHelper::IsNegInf(inf));
   EXPECT_FALSE(MathHelper::IsFinite(inf));
}

TEST(when_getting_negative_infinity, should_return_negative_infinity)
{
   double negInf = MathHelper::GetNegInf();
   EXPECT_TRUE(MathHelper::IsNegInf(negInf));
   EXPECT_FALSE(MathHelper::IsInf(negInf));
   EXPECT_FALSE(MathHelper::IsFinite(negInf));
}

TEST(when_checking_is_finite_for_regular_values, should_return_true)
{
   EXPECT_TRUE(MathHelper::IsFinite(0.0));
   EXPECT_TRUE(MathHelper::IsFinite(1.0));
   EXPECT_TRUE(MathHelper::IsFinite(-1e300));
}

TEST(when_checking_is_finite_for_nan, should_return_false)
{
   EXPECT_FALSE(MathHelper::IsFinite(MathHelper::GetNaN()));
}

TEST(when_getting_pi_value, should_return_correct_approximation)
{
   double pi = MathHelper::Pi();
   EXPECT_NEAR(3.14159265358979, pi, 1e-12);
}

TEST(when_checking_valid_numeric_strings, should_return_true)
{
   EXPECT_TRUE(MathHelper::IsNumeric("0"));
   EXPECT_TRUE(MathHelper::IsNumeric("123"));
   EXPECT_TRUE(MathHelper::IsNumeric("-456"));
   EXPECT_TRUE(MathHelper::IsNumeric("3.14"));
   EXPECT_TRUE(MathHelper::IsNumeric("1e10"));
   EXPECT_TRUE(MathHelper::IsNumeric("-2.5e-3"));
}

TEST(when_checking_invalid_numeric_strings, should_return_false)
{
   EXPECT_FALSE(MathHelper::IsNumeric(""));
   EXPECT_FALSE(MathHelper::IsNumeric("abc"));
   EXPECT_FALSE(MathHelper::IsNumeric("12abc"));
   EXPECT_FALSE(MathHelper::IsNumeric("hello world"));
}

TEST(when_converting_nan_to_string, should_return_nan_string)
{
   EXPECT_EQ("NaN", MathHelper::ToString(MathHelper::GetNaN()));
}

TEST(when_converting_positive_infinity_to_string, should_return_inf_string)
{
   EXPECT_EQ("Inf", MathHelper::ToString(MathHelper::GetInf()));
}

TEST(when_converting_negative_infinity_to_string, should_return_neg_inf_string)
{
   EXPECT_EQ("-Inf", MathHelper::ToString(MathHelper::GetNegInf()));
}

TEST(when_computing_normal_distribution_at_the_mean, should_return_the_peak_value)
{
   double peak = MathHelper::NormalDistribution(0.0, 1.0, 0.0);
   double expected = 1.0 / sqrt(2.0 * MathHelper::Pi());
   EXPECT_NEAR(expected, peak, 1e-12);
}

TEST(when_computing_normal_distribution_symmetrically_around_mean, should_return_equal_values_on_both_sides)
{
   double left = MathHelper::NormalDistribution(5.0, 2.0, 3.0);
   double right = MathHelper::NormalDistribution(5.0, 2.0, 7.0);
   EXPECT_NEAR(left, right, 1e-12);
}

TEST(when_computing_normal_distribution_away_from_mean, should_decrease_with_increasing_distance)
{
   double atMean = MathHelper::NormalDistribution(0.0, 1.0, 0.0);
   double atOne = MathHelper::NormalDistribution(0.0, 1.0, 1.0);
   double atTwo = MathHelper::NormalDistribution(0.0, 1.0, 2.0);
   EXPECT_GT(atMean, atOne);
   EXPECT_GT(atOne, atTwo);
}

TEST(when_computing_log_distribution_with_valid_parameters, should_produce_monotonically_increasing_values)
{
   constexpr long NUM_POINTS = 5;
   double values[NUM_POINTS];
   MathHelper::LogDistribution(1.0, 16.0, NUM_POINTS, values);

   EXPECT_DOUBLE_EQ(1.0, values[0]);
   EXPECT_DOUBLE_EQ(16.0, values[NUM_POINTS - 1]);
   for (long i = 1; i < NUM_POINTS; i++)
   {
      EXPECT_GT(values[i], values[i - 1]);
   }
}

TEST(when_computing_log_distribution_with_a_single_point, should_return_the_start_value)
{
   double values[1];
   MathHelper::LogDistribution(5.0, 10.0, 1, values);
   EXPECT_DOUBLE_EQ(5.0, values[0]);
}

TEST(when_computing_log_distribution_with_invalid_parameters, should_throw_error_data)
{
   double values[5];

   EXPECT_THROW(MathHelper::LogDistribution(0.0, 10.0, 5, values), ErrorData);
   EXPECT_THROW(MathHelper::LogDistribution(-5.0, 10.0, 5, values), ErrorData);
   EXPECT_THROW(MathHelper::LogDistribution(1.0, 10.0, 0, values), ErrorData);
}
