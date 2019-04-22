#pragma once

class CalculatorEngine
{
public:
	class ComputableLitteral {
		friend CalculatorEngine;

	public:
		explicit ComputableLitteral() {};
		explicit ComputableLitteral(const double numerator) : numerator_(numerator) {}
		explicit ComputableLitteral(const double numerator, const int denominator): numerator_(numerator), denominator_(denominator) {}

		const double getNumerator() const { return numerator_; }
		const double getDenominator() const { return denominator_; }

		bool simplify();

	private:
		double numerator_{0};
		int denominator_{1};
	};

	static ComputableLitteral makeAddition(const ComputableLitteral& rLitteral, const ComputableLitteral& lLitteral);

	static bool isInteger(const double value) { return floor(value) == ceil(value); }
	static int computeGreatestCommonDivisor(const int value1, const int value2);
};

CalculatorEngine::ComputableLitteral CalculatorEngine::makeAddition(const ComputableLitteral& rLitteral, const ComputableLitteral& lLitteral) {
	const int resultDenominator{ rLitteral.denominator_ * lLitteral.denominator_ };
	const double resultNumerator{ rLitteral.numerator_ * lLitteral.denominator_ + lLitteral.numerator_ * rLitteral.denominator_ };

	ComputableLitteral result{ resultNumerator, resultDenominator };

	result.simplify();
	return result;
}

int CalculatorEngine::computeGreatestCommonDivisor(const int value1, const int value2) {	
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
		const int left{ value1IsGreaterThanValue2 ? (value1 % value2) : (value2 % value1) };
		
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
	const int greatestCommonDivisor{ computeGreatestCommonDivisor(static_cast<int>(numerator_), denominator_) };
	numerator_ /= greatestCommonDivisor;
	denominator_ /= greatestCommonDivisor;

	return greatestCommonDivisor != 1;
}
