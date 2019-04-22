#include "gtest/gtest.h"
#include "AdvancedCalculator/calculator_engine/calculator_engine.h"

using ComputableLitteral = CalculatorEngine::ComputableLitteral;

ComputableLitteral makeIntegerLitteral(const int value) {
	return ComputableLitteral(value);
}

ComputableLitteral makeDecimalLitteral(const double value) {
	return ComputableLitteral(value);
}

ComputableLitteral makeRationalLitteral(const int numerator, const int denominator) {
	return ComputableLitteral(numerator, denominator);
}

bool areEqual(double lValue, double rValue) {
	return fabs(lValue - rValue) < DBL_EPSILON;
}

bool areEqual(const ComputableLitteral& lLitteral, const ComputableLitteral& rLitteral)
{
	return	areEqual(lLitteral.getNumerator(), rLitteral.getNumerator()) && 
			areEqual(lLitteral.getDenominator(), rLitteral.getDenominator());
}

void assertAdditionResult(const double rvalue, const double lvalue, const double result) {
	ComputableLitteral rightLitteral(rvalue);
	ComputableLitteral leftLitteral(lvalue);
	EXPECT_TRUE(areEqual(CalculatorEngine::makeAddition(rightLitteral, leftLitteral), ComputableLitteral(result)));
}

void assertAdditionResult(const ComputableLitteral& lLitteral, const ComputableLitteral& rLitteral, const ComputableLitteral& result) {
	EXPECT_TRUE(areEqual(CalculatorEngine::makeAddition(lLitteral, rLitteral), result));
}

void assertSimplificationResult(ComputableLitteral& litteralToSimplify, const ComputableLitteral& expectedSimplificationResult, const bool shouldBeSimplified) {
	const bool simplificationWasDone{ litteralToSimplify.simplify() };

	EXPECT_TRUE(areEqual(litteralToSimplify, expectedSimplificationResult));
	EXPECT_EQ(simplificationWasDone, shouldBeSimplified);
}

TEST(TestCalculatorEngine, TestAdditionsOfIntegerValues) {
	assertAdditionResult(0, 0, 0);
	assertAdditionResult(0, 1, 1);
	assertAdditionResult(1, 1, 2);
	assertAdditionResult(10, 10, 20);
}

TEST(TestCalculatorEngine, TestAdditionsOfDecimalValues) {
	assertAdditionResult(0.5, 0.5, 1);
	assertAdditionResult(0.6, 1.5, 2.1);
	assertAdditionResult(0.1561654, 0.1234564, 0.2796218);
}

TEST(TestCalculatorEngine, TestAdditionsOfRationnalValues) {
	assertAdditionResult(makeRationalLitteral(1, 2), makeIntegerLitteral(0), makeRationalLitteral(1, 2));
	assertAdditionResult(makeRationalLitteral(1, 2), makeRationalLitteral(1, 2), makeIntegerLitteral(1));
	assertAdditionResult(makeRationalLitteral(5, 4), makeRationalLitteral(27, 8), makeRationalLitteral(37, 8));
}

TEST(TestCalculatorEngine, TestSimplificationResult) {
	assertSimplificationResult(makeRationalLitteral(0, 4), makeIntegerLitteral(0), true);
	assertSimplificationResult(makeRationalLitteral(2, 2), makeIntegerLitteral(1), true);
	assertSimplificationResult(makeRationalLitteral(4, 2), makeIntegerLitteral(2), true);
	assertSimplificationResult(makeRationalLitteral(2, 4), makeRationalLitteral(1, 2), true);
	assertSimplificationResult(makeRationalLitteral(6, 4), makeRationalLitteral(3, 2), true);
	assertSimplificationResult(makeRationalLitteral(4, 6), makeRationalLitteral(2, 3), true);
	assertSimplificationResult(makeRationalLitteral(9, 3), makeRationalLitteral(3, 1), true);
	assertSimplificationResult(makeRationalLitteral(15, 10), makeRationalLitteral(3, 2), true);
	
	assertSimplificationResult(makeRationalLitteral(17, 11), makeRationalLitteral(17, 11), false);
	assertSimplificationResult(makeRationalLitteral(3, 2), makeRationalLitteral(3, 2), false);
	assertSimplificationResult(makeRationalLitteral(2, 3), makeRationalLitteral(2, 3), false);
	assertSimplificationResult(makeRationalLitteral(2, 1), makeIntegerLitteral(2), false);
	assertSimplificationResult(ComputableLitteral(0.4568, 5), ComputableLitteral(0.4568, 5), false);
}
