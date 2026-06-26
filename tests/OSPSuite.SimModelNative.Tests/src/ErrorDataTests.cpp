#include <gtest/gtest.h>
#include <ErrorData.h>

TEST(ErrorDataTest, DefaultConstructor_SetsOkAndEmptyStrings)
{
   ErrorData ed;
   EXPECT_EQ(ErrorData::ED_OK, ed.GetNumber());
   EXPECT_EQ("", ed.GetSource());
   EXPECT_EQ("", ed.GetDescription());
}

TEST(ErrorDataTest, ParameterizedConstructor_StoresValues)
{
   ErrorData ed(ErrorData::ED_ERROR, "TestSource", "Something went wrong");
   EXPECT_EQ(ErrorData::ED_ERROR, ed.GetNumber());
   EXPECT_EQ("TestSource", ed.GetSource());
   EXPECT_EQ("Something went wrong", ed.GetDescription());
}

TEST(ErrorDataTest, ParameterizedConstructor_CriticalError)
{
   ErrorData ed(ErrorData::ED_CRITICAL_ERROR, "CritSrc", "Fatal");
   EXPECT_EQ(ErrorData::ED_CRITICAL_ERROR, ed.GetNumber());
   EXPECT_EQ("CritSrc", ed.GetSource());
   EXPECT_EQ("Fatal", ed.GetDescription());
}

TEST(ErrorDataTest, SetNumber_GetNumber)
{
   ErrorData ed;
   ed.SetNumber(ErrorData::ED_CRITICAL_ERROR);
   EXPECT_EQ(ErrorData::ED_CRITICAL_ERROR, ed.GetNumber());

   ed.SetNumber(ErrorData::ED_ERROR);
   EXPECT_EQ(ErrorData::ED_ERROR, ed.GetNumber());
}

TEST(ErrorDataTest, SetSource_GetSource)
{
   ErrorData ed;
   ed.SetSource("MySource");
   EXPECT_EQ("MySource", ed.GetSource());
}

TEST(ErrorDataTest, SetDescription_GetDescription)
{
   ErrorData ed;
   ed.SetDescription("My description");
   EXPECT_EQ("My description", ed.GetDescription());
}

TEST(ErrorDataTest, AssignmentOperator_CopiesAllFields)
{
   ErrorData src(ErrorData::ED_ERROR, "Source1", "Desc1");
   ErrorData dest;
   dest = src;

   EXPECT_EQ(ErrorData::ED_ERROR, dest.GetNumber());
   EXPECT_EQ("Source1", dest.GetSource());
   EXPECT_EQ("Desc1", dest.GetDescription());
}

TEST(ErrorDataTest, AssignmentOperator_IndependentOfSource)
{
   ErrorData src(ErrorData::ED_ERROR, "Source1", "Desc1");
   ErrorData dest;
   dest = src;

   src.SetSource("Modified");
   EXPECT_EQ("Source1", dest.GetSource());
}

TEST(ErrorDataTest, Clear_ResetsToDefaults)
{
   ErrorData ed(ErrorData::ED_CRITICAL_ERROR, "Src", "Desc");
   ed.Clear();

   EXPECT_EQ(ErrorData::ED_OK, ed.GetNumber());
   EXPECT_EQ("", ed.GetSource());
   EXPECT_EQ("", ed.GetDescription());
}
