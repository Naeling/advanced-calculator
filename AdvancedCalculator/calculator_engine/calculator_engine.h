#pragma once

class CalculatorEngine
{
public:
	class ComputableLitteral {
		friend CalculatorEngine;

	public:
		explicit ComputableLitteral() {};
		explicit ComputableLitteral(const double numerator) : numerator(numerator) {}
		explicit ComputableLitteral(const double numerator, const int denominator): numerator(numerator), denominator(denominator) {}

		const double getNumerator() { return numerator; }
		const double getDenominator() { return denominator; }

	private:
		const double numerator{0};
		const int denominator{1};
	};

	static ComputableLitteral makeAddition(const ComputableLitteral& rLitteral, const ComputableLitteral& lLitteral) {
		const int resultDenominator{rLitteral.denominator * lLitteral.denominator};
		const double resultNumerator{rLitteral.numerator * lLitteral.denominator + lLitteral.numerator * rLitteral.denominator};
		ComputableLitteral result{resultNumerator, resultDenominator};		
		return result;
	}
};
