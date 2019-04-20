#include "gtest/gtest.h"
#include "AdvancedCalculator/calculator_engine/calculator_engine.h"


bool AreEqual(double rValue, double lValue) {
	return fabs(rValue - lValue) < DBL_EPSILON;
}

void AssertAdditionResult(const double rvalue, const double lvalue, const double result) {
	CalculatorEngine::ComputableLitteral rightLitteral(rvalue);
	CalculatorEngine::ComputableLitteral leftLitteral(lvalue);
	EXPECT_TRUE(AreEqual(CalculatorEngine::makeAddition(rightLitteral, leftLitteral), result));
}

TEST(TestCalculatorEngine, TestAdditionsOfSingleValues) {
	AssertAdditionResult(0, 0, 0);
	AssertAdditionResult(0, 1, 1);
	AssertAdditionResult(1, 1, 2);
	AssertAdditionResult(10, 10, 20);
	AssertAdditionResult(0.5, 0.5, 1);
	AssertAdditionResult(0.6, 1.5, 2.1);
	AssertAdditionResult(0.1561654, 0.1234564, 0.2796218);
}

TEST(TestCalculatorEngine, TestAdditionsOfRationnalValues) {

}
