#include "AdvancedCalculator/calculator_engine/calculator_engine.h"

const bool CalculatorEngine::ComputableLitteral::operator==(ComputableLitteral rLitteral) const {
	ComputableLitteral lLitteral = *this;

	lLitteral.simplify();
	rLitteral.simplify();

	return (fabs(lLitteral.numerator_ - rLitteral.numerator_) < DBL_EPSILON) && (lLitteral.denominator_ == rLitteral.denominator_);
}

CalculatorEngine::ComputableLitteral CalculatorEngine::makeAddition(const ComputableLitteral & rLitteral, const ComputableLitteral & lLitteral) {
	const long long resultDenominator{ rLitteral.denominator_ * lLitteral.denominator_ };
	const long double resultNumerator{ rLitteral.numerator_ * lLitteral.denominator_ + lLitteral.numerator_ * rLitteral.denominator_ };

	ComputableLitteral result{ resultNumerator, resultDenominator };

	result.simplify();
	return result;
}

long long CalculatorEngine::computeGreatestCommonDivisor(const long long value1, const long long value2) {
	if (value1 == value2) {
		return value1;
	}
	else if (value1 == 0)
	{
		return value2;
	}
	else if (value2 == 0)
	{
		return value1;
	}
	else {
		const bool value1IsGreaterThanValue2{ value1 > value2 };
		const long long left{ value1IsGreaterThanValue2 ? (value1 % value2) : (value2 % value1) };

		if (value1IsGreaterThanValue2)
			return computeGreatestCommonDivisor(left, value2);
		else
			return computeGreatestCommonDivisor(value1, left);
	}
}

bool CalculatorEngine::ComputableLitteral::simplify() {
	if (denominator_ == 1 || !isInteger(numerator_))
		return false;

	if (numerator_ == 0) {
		denominator_ = 1;
		return true;
	}

	simplifyMinusSign();

	//At this point, numerator_ is known to be an Integer
	const long long greatestCommonDivisor{ computeGreatestCommonDivisor(abs(static_cast<long long>(numerator_)), abs(denominator_)) };
	numerator_ /= greatestCommonDivisor;
	denominator_ /= greatestCommonDivisor;

	return greatestCommonDivisor != 1;
}