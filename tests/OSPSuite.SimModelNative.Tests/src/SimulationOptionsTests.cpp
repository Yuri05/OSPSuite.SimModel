#include <gtest/gtest.h>
#include "SimModel/SimulationOptions.h"

using namespace SimModelNative;

TEST(SimulationOptionsTest, DefaultConstructor_SetsExpectedDefaults)
{
   SimulationOptions opts;

   EXPECT_FALSE(opts.ShowProgress());
   EXPECT_DOUBLE_EQ(0.0, opts.ExecutionTimeLimit());
   EXPECT_TRUE(opts.StopOnWarnings());
   EXPECT_TRUE(opts.AutoReduceTolerances());
   EXPECT_TRUE(opts.WriteLogFile());
   EXPECT_FALSE(opts.ValidateWithXMLSchema());
   EXPECT_FALSE(opts.KeepXMLNodeAsString());
   EXPECT_TRUE(opts.UseFloatComparisonInUserOutputTimePoints());
   EXPECT_FALSE(opts.IdentifyUsedParameters());
}

TEST(SimulationOptionsTest, ShowProgress_RoundTrip)
{
   SimulationOptions opts;
   opts.SetShowProgress(true);
   EXPECT_TRUE(opts.ShowProgress());
   opts.SetShowProgress(false);
   EXPECT_FALSE(opts.ShowProgress());
}

TEST(SimulationOptionsTest, ExecutionTimeLimit_RoundTrip)
{
   SimulationOptions opts;
   opts.SetExecutionTimeLimit(42.5);
   EXPECT_DOUBLE_EQ(42.5, opts.ExecutionTimeLimit());
}

TEST(SimulationOptionsTest, StopOnWarnings_RoundTrip)
{
   SimulationOptions opts;
   opts.SetStopOnWarnings(false);
   EXPECT_FALSE(opts.StopOnWarnings());
   opts.SetStopOnWarnings(true);
   EXPECT_TRUE(opts.StopOnWarnings());
}

TEST(SimulationOptionsTest, AutoReduceTolerances_RoundTrip)
{
   SimulationOptions opts;
   opts.SetAutoReduceTolerances(false);
   EXPECT_FALSE(opts.AutoReduceTolerances());
}

TEST(SimulationOptionsTest, WriteLogFile_RoundTrip)
{
   SimulationOptions opts;
   opts.WriteLogFile(false);
   EXPECT_FALSE(opts.WriteLogFile());
}

TEST(SimulationOptionsTest, ValidateWithXMLSchema_RoundTrip)
{
   SimulationOptions opts;
   opts.ValidateWithXMLSchema(true);
   EXPECT_TRUE(opts.ValidateWithXMLSchema());
}

TEST(SimulationOptionsTest, KeepXMLNodeAsString_RoundTrip)
{
   SimulationOptions opts;
   opts.SetKeepXMLNodeAsString(true);
   EXPECT_TRUE(opts.KeepXMLNodeAsString());
}

TEST(SimulationOptionsTest, UseFloatComparison_RoundTrip)
{
   SimulationOptions opts;
   opts.SetUseFloatComparisonInUserOutputTimePoints(false);
   EXPECT_FALSE(opts.UseFloatComparisonInUserOutputTimePoints());
}

TEST(SimulationOptionsTest, IdentifyUsedParameters_RoundTrip)
{
   SimulationOptions opts;
   opts.IdentifyUsedParameters(true);
   EXPECT_TRUE(opts.IdentifyUsedParameters());
}

TEST(SimulationOptionsTest, LogFile_RoundTrip)
{
   SimulationOptions opts;
   EXPECT_EQ("", opts.LogFile());
   opts.SetLogFile("C:\\logs\\test.log");
   EXPECT_EQ("C:\\logs\\test.log", opts.LogFile());
}

TEST(SimulationOptionsTest, CopyFrom_CopiesAllProperties)
{
   SimulationOptions src;
   src.SetShowProgress(true);
   src.SetExecutionTimeLimit(100.0);
   src.SetStopOnWarnings(false);
   src.SetAutoReduceTolerances(false);
   src.WriteLogFile(false);
   src.ValidateWithXMLSchema(true);
   src.SetKeepXMLNodeAsString(true);
   src.SetUseFloatComparisonInUserOutputTimePoints(false);
   src.IdentifyUsedParameters(true);

   SimulationOptions dest;
   dest.CopyFrom(src);

   EXPECT_TRUE(dest.ShowProgress());
   EXPECT_DOUBLE_EQ(100.0, dest.ExecutionTimeLimit());
   EXPECT_FALSE(dest.StopOnWarnings());
   EXPECT_FALSE(dest.AutoReduceTolerances());
   EXPECT_FALSE(dest.WriteLogFile());
   EXPECT_TRUE(dest.ValidateWithXMLSchema());
   EXPECT_TRUE(dest.KeepXMLNodeAsString());
   EXPECT_FALSE(dest.UseFloatComparisonInUserOutputTimePoints());
   EXPECT_TRUE(dest.IdentifyUsedParameters());
}
