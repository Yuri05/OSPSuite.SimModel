#include <gtest/gtest.h>
#include "SimModel/SimulationOptions.h"

using namespace SimModelNative;

TEST(when_creating_simulation_options_with_default_constructor, should_set_all_expected_default_values)
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

TEST(when_toggling_show_progress_option, should_return_the_updated_value)
{
   SimulationOptions opts;
   opts.SetShowProgress(true);
   EXPECT_TRUE(opts.ShowProgress());
   opts.SetShowProgress(false);
   EXPECT_FALSE(opts.ShowProgress());
}

TEST(when_setting_execution_time_limit, should_return_the_updated_value)
{
   SimulationOptions opts;
   opts.SetExecutionTimeLimit(42.5);
   EXPECT_DOUBLE_EQ(42.5, opts.ExecutionTimeLimit());
}

TEST(when_toggling_stop_on_warnings_option, should_return_the_updated_value)
{
   SimulationOptions opts;
   opts.SetStopOnWarnings(false);
   EXPECT_FALSE(opts.StopOnWarnings());
   opts.SetStopOnWarnings(true);
   EXPECT_TRUE(opts.StopOnWarnings());
}

TEST(when_disabling_auto_reduce_tolerances, should_return_false)
{
   SimulationOptions opts;
   opts.SetAutoReduceTolerances(false);
   EXPECT_FALSE(opts.AutoReduceTolerances());
}

TEST(when_disabling_write_log_file, should_return_false)
{
   SimulationOptions opts;
   opts.WriteLogFile(false);
   EXPECT_FALSE(opts.WriteLogFile());
}

TEST(when_enabling_validate_with_xml_schema, should_return_true)
{
   SimulationOptions opts;
   opts.ValidateWithXMLSchema(true);
   EXPECT_TRUE(opts.ValidateWithXMLSchema());
}

TEST(when_enabling_keep_xml_node_as_string, should_return_true)
{
   SimulationOptions opts;
   opts.SetKeepXMLNodeAsString(true);
   EXPECT_TRUE(opts.KeepXMLNodeAsString());
}

TEST(when_disabling_use_float_comparison_in_output_time_points, should_return_false)
{
   SimulationOptions opts;
   opts.SetUseFloatComparisonInUserOutputTimePoints(false);
   EXPECT_FALSE(opts.UseFloatComparisonInUserOutputTimePoints());
}

TEST(when_enabling_identify_used_parameters, should_return_true)
{
   SimulationOptions opts;
   opts.IdentifyUsedParameters(true);
   EXPECT_TRUE(opts.IdentifyUsedParameters());
}

TEST(when_setting_log_file_path, should_return_the_updated_path)
{
   SimulationOptions opts;
   EXPECT_EQ("", opts.LogFile());
   opts.SetLogFile("C:\\logs\\test.log");
   EXPECT_EQ("C:\\logs\\test.log", opts.LogFile());
}

TEST(when_copying_simulation_options_from_another_instance, should_copy_all_properties_correctly)
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
   src.SetLogFile("copied.log");

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
   EXPECT_EQ("copied.log", dest.LogFile());
}
