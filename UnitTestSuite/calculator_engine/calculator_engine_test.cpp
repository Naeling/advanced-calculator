#include "gtest/gtest.h"
#include "AdvancedCalculator/calculator_engine/calculator_engine.h"

using ComputableLitteral = CalculatorEngine::ComputableLitteral;

bool areEqual(double lValue, double rValue) {
	return fabs(lValue - rValue) < DBL_EPSILON;
}

bool areEqual(ComputableLitteral lLitteral, ComputableLitteral rLitteral)
{
	return	areEqual(lLitteral.getNumerator(), rLitteral.getNumerator()) && 
			areEqual(lLitteral.getDenominator(), rLitteral.getDenominator());
}

void assertAdditionResult(const double rvalue, const double lvalue, const double result) {
	ComputableLitteral rightLitteral(rvalue);
	ComputableLitteral leftLitteral(lvalue);
	EXPECT_TRUE(areEqual(CalculatorEngine::makeAddition(rightLitteral, leftLitteral), ComputableLitteral(result)));
}

void assertAdditionResult(const ComputableLitteral lLitteral, const ComputableLitteral rLitteral, const ComputableLitteral result) {
	EXPECT_TRUE(areEqual(CalculatorEngine::makeAddition(lLitteral, rLitteral), result));
}

TEST(TestCalculatorEngine, TestAdditionsOfSingleValues) {
	//Integers
	assertAdditionResult(0, 0, 0);
	assertAdditionResult(0, 1, 1);
	assertAdditionResult(1, 1, 2);
	assertAdditionResult(10, 10, 20);
	
	//Floating points
	assertAdditionResult(0.5, 0.5, 1);
	assertAdditionResult(0.6, 1.5, 2.1);
	assertAdditionResult(0.1561654, 0.1234564, 0.2796218);

	//Rationnal
	assertAdditionResult(ComputableLitteral(1, 2), ComputableLitteral(0), ComputableLitteral(1, 2));
}

TEST(TestCalculatorEngine, ) {
	CalculatorEngine::ComputableLitteral rightLitteral(1, 2);
	CalculatorEngine::ComputableLitteral leftLitteral(1);
	EXPECT_TRUE(areEqual(CalculatorEngine::makeAddition(rightLitteral, leftLitteral), ComputableLitteral(3, 2)));
}

TEST(TestCalculatorEngine, TestAdditionsOfRationnalValues) {
	CalculatorEngine::ComputableLitteral rightLitteral(1, 2);
	CalculatorEngine::ComputableLitteral leftLitteral(1, 2);
	EXPECT_TRUE(areEqual(CalculatorEngine::makeAddition(rightLitteral, leftLitteral), ComputableLitteral(4, 4)));
}
