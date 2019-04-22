#include "gtest/gtest.h"
#include "AdvancedCalculator/calculator_engine/calculator_engine.h"

using ComputableLitteral = CalculatorEngine::ComputableLitteral;

ComputableLitteral makeSimpleLitteral(const long double value) {
	return ComputableLitteral(value);
}

ComputableLitteral makeRationalLitteral(const long double numerator, const long long denominator) {
	return ComputableLitteral(numerator, denominator);
}

void assertAdditionResult(const long double lValue, const long double rValue, const long double result) {
	ComputableLitteral lLitteral(lValue);
	ComputableLitteral rLitteral(rValue);

	EXPECT_TRUE(CalculatorEngine::makeAddition(lLitteral, rLitteral) == ComputableLitteral(result));
}

void assertAdditionResult(const ComputableLitteral& lLitteral, const ComputableLitteral& rLitteral, const ComputableLitteral& result) {
	EXPECT_TRUE(CalculatorEngine::makeAddition(lLitteral, rLitteral) == result);
}

void assertSimplificationResult(ComputableLitteral& litteralToSimplify, const ComputableLitteral& expectedSimplificationResult, const bool shouldBeSimplified) {
	const bool simplificationWasDone{ litteralToSimplify.simplify() };

	EXPECT_TRUE(litteralToSimplify == expectedSimplificationResult);
	EXPECT_EQ(simplificationWasDone, shouldBeSimplified);
}

TEST(TestCalculatorEngine, TestAdditionsOfIntegerValues) {
	assertAdditionResult(0, 0, 0);
	assertAdditionResult(0, 1, 1);
	assertAdditionResult(1, 1, 2);
	assertAdditionResult(10, 10, 20);

	assertAdditionResult(-1, 0, -1);
	assertAdditionResult(-10, -3, -13);
	assertAdditionResult(3, -10, -7);
}

TEST(TestCalculatorEngine, TestAdditionsOfDecimalValues) {
	assertAdditionResult(0.5, 0.5, 1);
	assertAdditionResult(0.6, 1.5, 2.1);

	assertAdditionResult(-0.5, -0.5, -1);
	assertAdditionResult(-0.6, -1.5, -2.1);
	assertAdditionResult(-0.6, 1.5, 0.9);

	assertAdditionResult(0.1561654, 0.1234564, 0.2796218);
	assertAdditionResult(-0.1561654, -0.1234564, -0.2796218);
	assertAdditionResult(-0.1561654, 0.1234564, -0.032709);
}

TEST(TestCalculatorEngine, TestAdditionsOfRationnalValues) {
	assertAdditionResult(makeRationalLitteral(1, 2), makeSimpleLitteral(0), makeRationalLitteral(1, 2));
	assertAdditionResult(makeRationalLitteral(1, 2), makeRationalLitteral(1, 2), makeSimpleLitteral(1));
	assertAdditionResult(makeRationalLitteral(5, 4), makeRationalLitteral(27, 8), makeRationalLitteral(37, 8));
	assertAdditionResult(makeRationalLitteral(1524897, 13245), makeRationalLitteral(465786, 12346579), makeRationalLitteral(6277810204311, 54510146285));

	assertAdditionResult(makeRationalLitteral(-1, 2), makeSimpleLitteral(0), makeRationalLitteral(1, -2));
	assertAdditionResult(makeRationalLitteral(1, -2), makeRationalLitteral(-1, 2), makeSimpleLitteral(-1));
	assertAdditionResult(makeRationalLitteral(-5, 4), makeRationalLitteral(27, -8), makeRationalLitteral(-37, 8));
	assertAdditionResult(makeRationalLitteral(-1524897, 13245), makeRationalLitteral(465786, -12346579), makeRationalLitteral(-6277810204311, 54510146285));

	assertAdditionResult(makeRationalLitteral(-5, 4), makeRationalLitteral(27, 8), makeRationalLitteral(17, 8));
	assertAdditionResult(makeRationalLitteral(5, 4), makeRationalLitteral(-27, 8), makeRationalLitteral(-17, 8));
}

TEST(TestCalculatorEngine, TestSimplificationResult) {
	assertSimplificationResult(makeRationalLitteral(0, 4), makeSimpleLitteral(0), true);
	assertSimplificationResult(makeRationalLitteral(2, 2), makeSimpleLitteral(1), true);
	assertSimplificationResult(makeRationalLitteral(4, 2), makeSimpleLitteral(2), true);
	assertSimplificationResult(makeRationalLitteral(2, 4), makeRationalLitteral(1, 2), true);
	assertSimplificationResult(makeRationalLitteral(6, 4), makeRationalLitteral(3, 2), true);
	assertSimplificationResult(makeRationalLitteral(4, 6), makeRationalLitteral(2, 3), true);
	assertSimplificationResult(makeRationalLitteral(9, 3), makeRationalLitteral(3, 1), true);
	assertSimplificationResult(makeRationalLitteral(15, 10), makeRationalLitteral(3, 2), true);
	
	assertSimplificationResult(makeRationalLitteral(-0, -4), makeSimpleLitteral(0), true);
	assertSimplificationResult(makeRationalLitteral(2, -2), makeSimpleLitteral(-1), true);
	assertSimplificationResult(makeRationalLitteral(-15, 10), makeRationalLitteral(-3, 2), true);
	assertSimplificationResult(makeRationalLitteral(15, -10), makeRationalLitteral(3, -2), true);

	assertSimplificationResult(makeRationalLitteral(17, 11), makeRationalLitteral(17, 11), false);
	assertSimplificationResult(makeRationalLitteral(3, 2), makeRationalLitteral(3, 2), false);
	assertSimplificationResult(makeRationalLitteral(2, 3), makeRationalLitteral(2, 3), false);
	assertSimplificationResult(makeRationalLitteral(2, 1), makeSimpleLitteral(2), false);
	assertSimplificationResult(ComputableLitteral(0.4568, 5), ComputableLitteral(0.4568, 5), false);
}
