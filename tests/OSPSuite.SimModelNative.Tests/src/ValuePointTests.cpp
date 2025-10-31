#include <gtest/gtest.h>
#include "SimModel/Formula.h"

using namespace SimModelNative;

// Test suite for ValuePoint
class ValuePointTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Common setup for each test
    }
};

TEST_F(ValuePointTest, DefaultConstructor) {
    ValuePoint point;
    EXPECT_EQ(point.X, 0.0);
    EXPECT_EQ(point.Y, 0.0);
    EXPECT_FALSE(point.RestartSolver);
}

TEST_F(ValuePointTest, ParameterizedConstructor) {
    ValuePoint point(1.5, 2.5, true);
    EXPECT_EQ(point.X, 1.5);
    EXPECT_EQ(point.Y, 2.5);
    EXPECT_TRUE(point.RestartSolver);
}

TEST_F(ValuePointTest, ParameterizedConstructorNoRestart) {
    ValuePoint point(3.0, 4.0, false);
    EXPECT_EQ(point.X, 3.0);
    EXPECT_EQ(point.Y, 4.0);
    EXPECT_FALSE(point.RestartSolver);
}

TEST_F(ValuePointTest, CopyConstructor) {
    ValuePoint original(5.5, 6.5, true);
    ValuePoint copy(original);
    
    EXPECT_EQ(copy.X, original.X);
    EXPECT_EQ(copy.Y, original.Y);
    EXPECT_EQ(copy.RestartSolver, original.RestartSolver);
    
    EXPECT_EQ(copy.X, 5.5);
    EXPECT_EQ(copy.Y, 6.5);
    EXPECT_TRUE(copy.RestartSolver);
}

TEST_F(ValuePointTest, CopyConstructorIndependent) {
    ValuePoint original(7.0, 8.0, false);
    ValuePoint copy(original);
    
    // Modify the copy
    copy.X = 10.0;
    copy.Y = 11.0;
    copy.RestartSolver = true;
    
    // Original should remain unchanged
    EXPECT_EQ(original.X, 7.0);
    EXPECT_EQ(original.Y, 8.0);
    EXPECT_FALSE(original.RestartSolver);
}

TEST_F(ValuePointTest, NegativeValues) {
    ValuePoint point(-1.5, -2.5, true);
    EXPECT_EQ(point.X, -1.5);
    EXPECT_EQ(point.Y, -2.5);
    EXPECT_TRUE(point.RestartSolver);
}

TEST_F(ValuePointTest, ZeroValues) {
    ValuePoint point(0.0, 0.0, false);
    EXPECT_EQ(point.X, 0.0);
    EXPECT_EQ(point.Y, 0.0);
    EXPECT_FALSE(point.RestartSolver);
}

TEST_F(ValuePointTest, LargeValues) {
    ValuePoint point(1e10, 1e-10, true);
    EXPECT_EQ(point.X, 1e10);
    EXPECT_EQ(point.Y, 1e-10);
    EXPECT_TRUE(point.RestartSolver);
}
