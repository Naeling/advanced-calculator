#pragma once

class CalculatorEngine
{
public:
	class ComputableLitteral {
		friend CalculatorEngine;

	public:
		explicit ComputableLitteral() {};
		explicit ComputableLitteral(const long double numerator) : numerator_(numerator) {}
		explicit ComputableLitteral(const long double numerator, const long long denominator): numerator_(numerator), denominator_(denominator) {}

		const long double getNumerator() const { return numerator_; }
		const long long getDenominator() const { return denominator_; }

		bool simplify();

	private:
		long double numerator_{0};
		long long denominator_{1};
	};

	static ComputableLitteral makeAddition(const ComputableLitteral& rLitteral, const ComputableLitteral& lLitteral);

	static bool isInteger(const long double value) { return floor(value) == ceil(value); }
	static long long computeGreatestCommonDivisor(const long long value1, const long long value2);
};

CalculatorEngine::ComputableLitteral CalculatorEngine::makeAddition(const ComputableLitteral& rLitteral, const ComputableLitteral& lLitteral) {
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
		
		if(value1IsGreaterThanValue2)
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

	//At this point, numerator_ is known to be an Integer
	const long long numerator = abs(static_cast<long long>(numerator_));
	const long long greatestCommonDivisor{ computeGreatestCommonDivisor(numerator, abs(denominator_)) };
	numerator_ /= greatestCommonDivisor;
	denominator_ /= greatestCommonDivisor;

	return greatestCommonDivisor != 1;
}
