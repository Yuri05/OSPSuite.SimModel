#include <gtest/gtest.h>
#include "SimModel/MathHelper.h"
#include "SimModel/ConstantFormula.h"
#include <cmath>
#include <limits>

using namespace SimModelNative;

// Test suite for MathHelper
class MathHelperTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Common setup for each test
    }
};

TEST_F(MathHelperTest, GetNaN) {
    double nan_val = MathHelper::GetNaN();
    EXPECT_TRUE(std::isnan(nan_val));
}

TEST_F(MathHelperTest, IsNaN) {
    EXPECT_TRUE(MathHelper::IsNaN(MathHelper::GetNaN()));
    EXPECT_FALSE(MathHelper::IsNaN(0.0));
    EXPECT_FALSE(MathHelper::IsNaN(1.0));
    EXPECT_FALSE(MathHelper::IsNaN(-1.0));
}

TEST_F(MathHelperTest, GetInf) {
    double inf_val = MathHelper::GetInf();
    EXPECT_TRUE(std::isinf(inf_val));
    EXPECT_GT(inf_val, 0);
}

TEST_F(MathHelperTest, GetNegInf) {
    double neg_inf_val = MathHelper::GetNegInf();
    EXPECT_TRUE(std::isinf(neg_inf_val));
    EXPECT_LT(neg_inf_val, 0);
}

TEST_F(MathHelperTest, IsFinite) {
    EXPECT_TRUE(MathHelper::IsFinite(0.0));
    EXPECT_TRUE(MathHelper::IsFinite(1.0));
    EXPECT_TRUE(MathHelper::IsFinite(-1.0));
    EXPECT_TRUE(MathHelper::IsFinite(1e100));
    EXPECT_FALSE(MathHelper::IsFinite(MathHelper::GetInf()));
    EXPECT_FALSE(MathHelper::IsFinite(MathHelper::GetNegInf()));
    EXPECT_FALSE(MathHelper::IsFinite(MathHelper::GetNaN()));
}

TEST_F(MathHelperTest, IsInf) {
    EXPECT_TRUE(MathHelper::IsInf(MathHelper::GetInf()));
    EXPECT_FALSE(MathHelper::IsInf(MathHelper::GetNegInf()));
    EXPECT_FALSE(MathHelper::IsInf(0.0));
    EXPECT_FALSE(MathHelper::IsInf(MathHelper::GetNaN()));
}

TEST_F(MathHelperTest, IsNegInf) {
    EXPECT_TRUE(MathHelper::IsNegInf(MathHelper::GetNegInf()));
    EXPECT_FALSE(MathHelper::IsNegInf(MathHelper::GetInf()));
    EXPECT_FALSE(MathHelper::IsNegInf(0.0));
    EXPECT_FALSE(MathHelper::IsNegInf(MathHelper::GetNaN()));
}

TEST_F(MathHelperTest, IsNumeric) {
    EXPECT_TRUE(MathHelper::IsNumeric("123"));
    EXPECT_TRUE(MathHelper::IsNumeric("123.456"));
    EXPECT_TRUE(MathHelper::IsNumeric("-123.456"));
    EXPECT_TRUE(MathHelper::IsNumeric("0.0"));
    EXPECT_TRUE(MathHelper::IsNumeric("1e10"));
    EXPECT_FALSE(MathHelper::IsNumeric(""));
    EXPECT_FALSE(MathHelper::IsNumeric("abc"));
    EXPECT_FALSE(MathHelper::IsNumeric("12.34.56"));
}

TEST_F(MathHelperTest, Pi) {
    double pi = MathHelper::Pi();
    EXPECT_NEAR(pi, 3.14159265358979323846, 1e-10);
}

TEST_F(MathHelperTest, NormalDistribution) {
    // Test normal distribution at mean
    double result = MathHelper::NormalDistribution(0.0, 1.0, 0.0);
    EXPECT_NEAR(result, 1.0 / std::sqrt(2.0 * MathHelper::Pi()), 1e-10);
    
    // Test that it's symmetric
    double result1 = MathHelper::NormalDistribution(0.0, 1.0, 1.0);
    double result2 = MathHelper::NormalDistribution(0.0, 1.0, -1.0);
    EXPECT_NEAR(result1, result2, 1e-10);
}

TEST_F(MathHelperTest, ToString) {
    EXPECT_EQ(MathHelper::ToString(MathHelper::GetNaN()), "NaN");
    EXPECT_EQ(MathHelper::ToString(MathHelper::GetInf()), "Inf");
    EXPECT_EQ(MathHelper::ToString(MathHelper::GetNegInf()), "-Inf");
    // Regular numbers will be converted using XMLHelper::ToString
}

TEST_F(MathHelperTest, LogDistribution) {
    const long NUM_POINTS = 10;
    double values[NUM_POINTS];
    
    // Test valid case
    EXPECT_NO_THROW(MathHelper::LogDistribution(1.0, 100.0, NUM_POINTS, values));
    
    // First and last values should match min and max
    EXPECT_NEAR(values[0], 1.0, 1e-10);
    EXPECT_NEAR(values[NUM_POINTS - 1], 100.0, 1e-6);
    
    // Values should be increasing
    for (long i = 1; i < NUM_POINTS; i++) {
        EXPECT_GT(values[i], values[i - 1]);
    }
}

// Test suite for ConstantFormula
class ConstantFormulaTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Common setup for each test
    }
};

TEST_F(ConstantFormulaTest, DefaultConstructor) {
    ConstantFormula formula;
    // Default constructed formula should compute to 0.0
    EXPECT_EQ(formula.DE_Compute(nullptr, 0.0, Formula::ignore), 0.0);
}

TEST_F(ConstantFormulaTest, ValueConstructor) {
    ConstantFormula formula(42.5);
    EXPECT_EQ(formula.DE_Compute(nullptr, 0.0, Formula::ignore), 42.5);
}

TEST_F(ConstantFormulaTest, SetValue) {
    ConstantFormula formula;
    formula.SetValue(123.456);
    EXPECT_EQ(formula.DE_Compute(nullptr, 0.0, Formula::ignore), 123.456);
}

TEST_F(ConstantFormulaTest, IsZero) {
    ConstantFormula zero_formula(0.0);
    EXPECT_TRUE(zero_formula.IsZero());
    
    ConstantFormula non_zero_formula(1.0);
    EXPECT_FALSE(non_zero_formula.IsZero());
}

TEST_F(ConstantFormulaTest, IsConstant) {
    ConstantFormula formula(5.0);
    EXPECT_TRUE(formula.IsConstant(true));
    EXPECT_TRUE(formula.IsConstant(false));
}

TEST_F(ConstantFormulaTest, Clone) {
    ConstantFormula original(99.9);
    Formula* cloned = original.clone();
    
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->DE_Compute(nullptr, 0.0, Formula::ignore), 99.9);
    
    delete cloned;
}

TEST_F(ConstantFormulaTest, DE_Jacobian) {
    ConstantFormula formula(10.0);
    Formula* jacobian = formula.DE_Jacobian(0);
    
    ASSERT_NE(jacobian, nullptr);
    // Derivative of a constant is always 0
    EXPECT_EQ(jacobian->DE_Compute(nullptr, 0.0, Formula::ignore), 0.0);
    
    delete jacobian;
}

TEST_F(ConstantFormulaTest, SwitchTimePoints) {
    ConstantFormula formula(10.0);
    std::vector<double> timePoints = formula.SwitchTimePoints();
    
    // Constant formula should have no switch time points
    EXPECT_TRUE(timePoints.empty());
}

TEST_F(ConstantFormulaTest, RecursiveSimplify) {
    ConstantFormula formula(7.5);
    Formula* simplified = formula.RecursiveSimplify();
    
    // Simplifying a constant returns itself
    EXPECT_EQ(simplified, &formula);
}

TEST_F(ConstantFormulaTest, NegativeValue) {
    ConstantFormula formula(-15.5);
    EXPECT_EQ(formula.DE_Compute(nullptr, 0.0, Formula::ignore), -15.5);
}

// Main function for running all tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
