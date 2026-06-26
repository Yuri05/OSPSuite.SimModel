#include <gtest/gtest.h>
#include "SimModel/ConstantFormula.h"
#include "SimModel/MathHelper.h"

using namespace SimModelNative;

TEST(ConstantFormulaTest, DefaultConstructor_ZeroInitialized)
{
   ConstantFormula formula;
   EXPECT_DOUBLE_EQ(0.0, formula.DE_Compute(nullptr, 0.0, IGNORE_SCALEFACTOR));
}

TEST(ConstantFormulaTest, ValueConstructor_StoresValue)
{
   ConstantFormula formula(3.14);
   EXPECT_DOUBLE_EQ(3.14, formula.DE_Compute(nullptr, 0.0, IGNORE_SCALEFACTOR));
}

TEST(ConstantFormulaTest, DE_Compute_IgnoresTimeAndY)
{
   ConstantFormula formula(42.0);
   double y[] = {1.0, 2.0, 3.0};

   EXPECT_DOUBLE_EQ(42.0, formula.DE_Compute(nullptr, 0.0, IGNORE_SCALEFACTOR));
   EXPECT_DOUBLE_EQ(42.0, formula.DE_Compute(y, 100.0, IGNORE_SCALEFACTOR));
   EXPECT_DOUBLE_EQ(42.0, formula.DE_Compute(y, -5.0, USE_SCALEFACTOR));
}

TEST(ConstantFormulaTest, IsZero_TrueForZero)
{
   ConstantFormula formula(0.0);
   EXPECT_TRUE(formula.IsZero());
}

TEST(ConstantFormulaTest, IsZero_FalseForNonZero)
{
   ConstantFormula formula(1.0);
   EXPECT_FALSE(formula.IsZero());

   ConstantFormula negFormula(-0.001);
   EXPECT_FALSE(negFormula.IsZero());
}

TEST(ConstantFormulaTest, IsConstant_AlwaysTrue)
{
   ConstantFormula formula(5.0);
   EXPECT_TRUE(formula.IsConstant(true));
   EXPECT_TRUE(formula.IsConstant(false));
}

TEST(ConstantFormulaTest, SetValue_ChangesComputedValue)
{
   ConstantFormula formula(1.0);
   EXPECT_DOUBLE_EQ(1.0, formula.DE_Compute(nullptr, 0.0, IGNORE_SCALEFACTOR));

   formula.SetValue(99.0);
   EXPECT_DOUBLE_EQ(99.0, formula.DE_Compute(nullptr, 0.0, IGNORE_SCALEFACTOR));
}

TEST(ConstantFormulaTest, Clone_CreatesIndependentCopy)
{
   ConstantFormula original(7.5);
   Formula* cloned = original.clone();

   EXPECT_DOUBLE_EQ(7.5, cloned->DE_Compute(nullptr, 0.0, IGNORE_SCALEFACTOR));

   original.SetValue(0.0);
   EXPECT_DOUBLE_EQ(7.5, cloned->DE_Compute(nullptr, 0.0, IGNORE_SCALEFACTOR));

   delete cloned;
}

TEST(ConstantFormulaTest, DE_Jacobian_ReturnsZeroConstant)
{
   ConstantFormula formula(42.0);
   Formula* jacobian = formula.DE_Jacobian(0);

   EXPECT_DOUBLE_EQ(0.0, jacobian->DE_Compute(nullptr, 0.0, IGNORE_SCALEFACTOR));

   delete jacobian;
}

TEST(ConstantFormulaTest, SwitchTimePoints_ReturnsEmpty)
{
   ConstantFormula formula(1.0);
   std::vector<double> points = formula.SwitchTimePoints();
   EXPECT_TRUE(points.empty());
}

TEST(ConstantFormulaTest, NegativeValue)
{
   ConstantFormula formula(-100.0);
   EXPECT_DOUBLE_EQ(-100.0, formula.DE_Compute(nullptr, 0.0, IGNORE_SCALEFACTOR));
   EXPECT_FALSE(formula.IsZero());
}

TEST(ConstantFormulaTest, RecursiveSimplify_ReturnsSelf)
{
   ConstantFormula formula(5.0);
   Formula* simplified = formula.RecursiveSimplify();
   EXPECT_EQ(&formula, simplified);
}
