#include <gtest/gtest.h>
#include <ErrorData.h>

TEST(when_creating_error_data_with_default_constructor, should_set_ok_status_and_empty_strings)
{
   ErrorData ed;
   EXPECT_EQ(ErrorData::ED_OK, ed.GetNumber());
   EXPECT_EQ("", ed.GetSource());
   EXPECT_EQ("", ed.GetDescription());
}

TEST(when_creating_error_data_with_error_status, should_store_all_provided_values)
{
   ErrorData ed(ErrorData::ED_ERROR, "TestSource", "Something went wrong");
   EXPECT_EQ(ErrorData::ED_ERROR, ed.GetNumber());
   EXPECT_EQ("TestSource", ed.GetSource());
   EXPECT_EQ("Something went wrong", ed.GetDescription());
}

TEST(when_creating_error_data_with_critical_error_status, should_store_all_provided_values)
{
   ErrorData ed(ErrorData::ED_CRITICAL_ERROR, "CritSrc", "Fatal");
   EXPECT_EQ(ErrorData::ED_CRITICAL_ERROR, ed.GetNumber());
   EXPECT_EQ("CritSrc", ed.GetSource());
   EXPECT_EQ("Fatal", ed.GetDescription());
}

TEST(when_setting_the_error_number, should_return_the_updated_number)
{
   ErrorData ed;
   ed.SetNumber(ErrorData::ED_CRITICAL_ERROR);
   EXPECT_EQ(ErrorData::ED_CRITICAL_ERROR, ed.GetNumber());

   ed.SetNumber(ErrorData::ED_ERROR);
   EXPECT_EQ(ErrorData::ED_ERROR, ed.GetNumber());
}

TEST(when_setting_the_source, should_return_the_updated_source)
{
   ErrorData ed;
   ed.SetSource("MySource");
   EXPECT_EQ("MySource", ed.GetSource());
}

TEST(when_setting_the_description, should_return_the_updated_description)
{
   ErrorData ed;
   ed.SetDescription("My description");
   EXPECT_EQ("My description", ed.GetDescription());
}

TEST(when_assigning_error_data_to_another_instance, should_copy_all_fields)
{
   ErrorData src(ErrorData::ED_ERROR, "Source1", "Desc1");
   ErrorData dest;
   dest = src;

   EXPECT_EQ(ErrorData::ED_ERROR, dest.GetNumber());
   EXPECT_EQ("Source1", dest.GetSource());
   EXPECT_EQ("Desc1", dest.GetDescription());
}

TEST(when_modifying_source_after_assignment, should_not_affect_the_copy)
{
   ErrorData src(ErrorData::ED_ERROR, "Source1", "Desc1");
   ErrorData dest;
   dest = src;

   src.SetSource("Modified");
   EXPECT_EQ("Source1", dest.GetSource());
}

TEST(when_clearing_error_data, should_reset_all_fields_to_defaults)
{
   ErrorData ed(ErrorData::ED_CRITICAL_ERROR, "Src", "Desc");
   ed.Clear();

   EXPECT_EQ(ErrorData::ED_OK, ed.GetNumber());
   EXPECT_EQ("", ed.GetSource());
   EXPECT_EQ("", ed.GetDescription());
}
