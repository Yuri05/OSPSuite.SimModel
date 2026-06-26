#include <gtest/gtest.h>
#include "SimModel/OutputSchema.h"
#include <ErrorData.h>

using namespace SimModelNative;

// --- OutputTimePoint tests ---

TEST(OutputTimePointTest, Constructor_StoresAllValues)
{
   OutputTimePoint tp(1.5, true, false, true);
   EXPECT_DOUBLE_EQ(1.5, tp.Time());
   EXPECT_TRUE(tp.SaveSystemSolution());
   EXPECT_FALSE(tp.IsSwitchTimePoint());
   EXPECT_TRUE(tp.RestartSystem());
}

TEST(OutputTimePointTest, Constructor_AllFalse)
{
   OutputTimePoint tp(0.0, false, false, false);
   EXPECT_DOUBLE_EQ(0.0, tp.Time());
   EXPECT_FALSE(tp.SaveSystemSolution());
   EXPECT_FALSE(tp.IsSwitchTimePoint());
   EXPECT_FALSE(tp.RestartSystem());
}

TEST(OutputTimePointTest, Constructor_AllTrue)
{
   OutputTimePoint tp(100.0, true, true, true);
   EXPECT_TRUE(tp.SaveSystemSolution());
   EXPECT_TRUE(tp.IsSwitchTimePoint());
   EXPECT_TRUE(tp.RestartSystem());
}

// --- OutputInterval tests ---

TEST(OutputIntervalTest, DefaultConstructor_SetsZerosAndEquidistant)
{
   OutputInterval interval;
   EXPECT_DOUBLE_EQ(0.0, interval.StartTime());
   EXPECT_DOUBLE_EQ(0.0, interval.EndTime());
   EXPECT_EQ(0, interval.NumberOfTimePoints());
   EXPECT_EQ(Equidistant, interval.IntervalDistribution());
}

TEST(OutputIntervalTest, ParameterizedConstructor_StoresValues)
{
   OutputInterval interval(1.0, 10.0, 5, Equidistant);
   EXPECT_DOUBLE_EQ(1.0, interval.StartTime());
   EXPECT_DOUBLE_EQ(10.0, interval.EndTime());
   EXPECT_EQ(5, interval.NumberOfTimePoints());
   EXPECT_EQ(Equidistant, interval.IntervalDistribution());
}

TEST(OutputIntervalTest, Setters_RoundTrip)
{
   OutputInterval interval;
   interval.SetStartTime(2.0);
   interval.SetEndTime(8.0);
   interval.NumberOfTimePoints(10);
   interval.SetOutputIntervalDistribution(Logarithmic);

   EXPECT_DOUBLE_EQ(2.0, interval.StartTime());
   EXPECT_DOUBLE_EQ(8.0, interval.EndTime());
   EXPECT_EQ(10, interval.NumberOfTimePoints());
   EXPECT_EQ(Logarithmic, interval.IntervalDistribution());
}

TEST(OutputIntervalTest, TimePoints_EquidistantDistribution)
{
   OutputInterval interval(0.0, 10.0, 6, Equidistant);
   std::vector<double> points = interval.TimePoints();

   ASSERT_EQ(6u, points.size());
   EXPECT_DOUBLE_EQ(0.0, points[0]);
   EXPECT_DOUBLE_EQ(2.0, points[1]);
   EXPECT_DOUBLE_EQ(4.0, points[2]);
   EXPECT_DOUBLE_EQ(6.0, points[3]);
   EXPECT_DOUBLE_EQ(8.0, points[4]);
   EXPECT_DOUBLE_EQ(10.0, points[5]);
}

TEST(OutputIntervalTest, TimePoints_TwoPoints)
{
   OutputInterval interval(0.0, 100.0, 2, Equidistant);
   std::vector<double> points = interval.TimePoints();

   ASSERT_EQ(2u, points.size());
   EXPECT_DOUBLE_EQ(0.0, points[0]);
   EXPECT_DOUBLE_EQ(100.0, points[1]);
}

TEST(OutputIntervalTest, TimePoints_SinglePoint_WhenStartEqualsEnd)
{
   OutputInterval interval(5.0, 5.0, 1, Equidistant);
   std::vector<double> points = interval.TimePoints();

   ASSERT_EQ(1u, points.size());
   EXPECT_DOUBLE_EQ(5.0, points[0]);
}

TEST(OutputIntervalTest, TimePoints_ThrowsWhenStartGreaterThanEnd)
{
   OutputInterval interval(10.0, 5.0, 3, Equidistant);
   EXPECT_THROW(interval.TimePoints(), ErrorData);
}

TEST(OutputIntervalTest, TimePoints_ThrowsWhenLessThanTwoPoints)
{
   OutputInterval interval(0.0, 10.0, 1, Equidistant);
   EXPECT_THROW(interval.TimePoints(), ErrorData);
}

TEST(OutputIntervalTest, TimePoints_ThrowsForLogarithmic)
{
   OutputInterval interval(1.0, 10.0, 5, Logarithmic);
   EXPECT_THROW(interval.TimePoints(), ErrorData);
}

TEST(OutputIntervalTest, TimePoints_EquidistantThreePoints)
{
   OutputInterval interval(0.0, 1.0, 3, Equidistant);
   std::vector<double> points = interval.TimePoints();

   ASSERT_EQ(3u, points.size());
   EXPECT_DOUBLE_EQ(0.0, points[0]);
   EXPECT_DOUBLE_EQ(0.5, points[1]);
   EXPECT_DOUBLE_EQ(1.0, points[2]);
}
