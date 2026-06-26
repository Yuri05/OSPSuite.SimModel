#include <gtest/gtest.h>
#include "SimModel/MathHelper.h"
#include <ErrorData.h>
#include <cmath>

using namespace SimModelNative;

TEST(MathHelperTest, GetNaN_ReturnsNaN)
{
   double nan = MathHelper::GetNaN();
   EXPECT_TRUE(MathHelper::IsNaN(nan));
}

TEST(MathHelperTest, IsNaN_FalseForRegularValues)
{
   EXPECT_FALSE(MathHelper::IsNaN(0.0));
   EXPECT_FALSE(MathHelper::IsNaN(1.0));
   EXPECT_FALSE(MathHelper::IsNaN(-1.0));
   EXPECT_FALSE(MathHelper::IsNaN(1e300));
}

TEST(MathHelperTest, IsNaN_FalseForInfinity)
{
   EXPECT_FALSE(MathHelper::IsNaN(MathHelper::GetInf()));
   EXPECT_FALSE(MathHelper::IsNaN(MathHelper::GetNegInf()));
}

TEST(MathHelperTest, GetInf_ReturnsPositiveInfinity)
{
   double inf = MathHelper::GetInf();
   EXPECT_TRUE(MathHelper::IsInf(inf));
   EXPECT_FALSE(MathHelper::IsNegInf(inf));
   EXPECT_FALSE(MathHelper::IsFinite(inf));
}

TEST(MathHelperTest, GetNegInf_ReturnsNegativeInfinity)
{
   double negInf = MathHelper::GetNegInf();
   EXPECT_TRUE(MathHelper::IsNegInf(negInf));
   EXPECT_FALSE(MathHelper::IsInf(negInf));
   EXPECT_FALSE(MathHelper::IsFinite(negInf));
}

TEST(MathHelperTest, IsFinite_TrueForRegularValues)
{
   EXPECT_TRUE(MathHelper::IsFinite(0.0));
   EXPECT_TRUE(MathHelper::IsFinite(1.0));
   EXPECT_TRUE(MathHelper::IsFinite(-1e300));
}

TEST(MathHelperTest, IsFinite_FalseForNaN)
{
   EXPECT_FALSE(MathHelper::IsFinite(MathHelper::GetNaN()));
}

TEST(MathHelperTest, Pi_ApproximatelyCorrect)
{
   double pi = MathHelper::Pi();
   EXPECT_NEAR(3.14159265358979, pi, 1e-12);
}

TEST(MathHelperTest, IsNumeric_ValidNumbers)
{
   EXPECT_TRUE(MathHelper::IsNumeric("0"));
   EXPECT_TRUE(MathHelper::IsNumeric("123"));
   EXPECT_TRUE(MathHelper::IsNumeric("-456"));
   EXPECT_TRUE(MathHelper::IsNumeric("3.14"));
   EXPECT_TRUE(MathHelper::IsNumeric("1e10"));
   EXPECT_TRUE(MathHelper::IsNumeric("-2.5e-3"));
}

TEST(MathHelperTest, IsNumeric_InvalidStrings)
{
   EXPECT_FALSE(MathHelper::IsNumeric(""));
   EXPECT_FALSE(MathHelper::IsNumeric("abc"));
   EXPECT_FALSE(MathHelper::IsNumeric("12abc"));
   EXPECT_FALSE(MathHelper::IsNumeric("hello world"));
}

TEST(MathHelperTest, ToString_NaN)
{
   EXPECT_EQ("NaN", MathHelper::ToString(MathHelper::GetNaN()));
}

TEST(MathHelperTest, ToString_Inf)
{
   EXPECT_EQ("Inf", MathHelper::ToString(MathHelper::GetInf()));
}

TEST(MathHelperTest, ToString_NegInf)
{
   EXPECT_EQ("-Inf", MathHelper::ToString(MathHelper::GetNegInf()));
}

TEST(MathHelperTest, NormalDistribution_PeakAtMean)
{
   double peak = MathHelper::NormalDistribution(0.0, 1.0, 0.0);
   double expected = 1.0 / sqrt(2.0 * MathHelper::Pi());
   EXPECT_NEAR(expected, peak, 1e-12);
}

TEST(MathHelperTest, NormalDistribution_SymmetricAroundMean)
{
   double left = MathHelper::NormalDistribution(5.0, 2.0, 3.0);
   double right = MathHelper::NormalDistribution(5.0, 2.0, 7.0);
   EXPECT_NEAR(left, right, 1e-12);
}

TEST(MathHelperTest, NormalDistribution_DecreasesAwayFromMean)
{
   double atMean = MathHelper::NormalDistribution(0.0, 1.0, 0.0);
   double atOne = MathHelper::NormalDistribution(0.0, 1.0, 1.0);
   double atTwo = MathHelper::NormalDistribution(0.0, 1.0, 2.0);
   EXPECT_GT(atMean, atOne);
   EXPECT_GT(atOne, atTwo);
}

TEST(MathHelperTest, LogDistribution_ProducesExpectedValues)
{
   const long NUM_POINTS = 5;
   double values[NUM_POINTS];
   MathHelper::LogDistribution(1.0, 16.0, NUM_POINTS, values);

   EXPECT_DOUBLE_EQ(1.0, values[0]);
   EXPECT_DOUBLE_EQ(16.0, values[NUM_POINTS - 1]);
   for (long i = 1; i < NUM_POINTS; i++)
   {
      EXPECT_GT(values[i], values[i - 1]);
   }
}

TEST(MathHelperTest, LogDistribution_SinglePoint)
{
   double values[1];
   MathHelper::LogDistribution(5.0, 10.0, 1, values);
   EXPECT_DOUBLE_EQ(5.0, values[0]);
}

TEST(MathHelperTest, LogDistribution_ThrowsOnInvalidParams)
{
   double values[5];

   EXPECT_THROW(MathHelper::LogDistribution(0.0, 10.0, 5, values), ErrorData);
   EXPECT_THROW(MathHelper::LogDistribution(-5.0, 10.0, 5, values), ErrorData);
   EXPECT_THROW(MathHelper::LogDistribution(1.0, 10.0, 0, values), ErrorData);
}
