#pragma once

#include <xutility>
#include <cfloat>

class CalculatorEngine
{
public:
	class ComputableLitteral {
		friend CalculatorEngine;

	public:
		explicit ComputableLitteral() {};
		explicit ComputableLitteral(const long double numerator) : numerator_(numerator) {}
		explicit ComputableLitteral(const long double numerator, const long long denominator): numerator_(numerator), denominator_(denominator) {}

		const bool operator==(ComputableLitteral rLitteral) const;

		const long double getNumerator() const { return numerator_; }
		const long long getDenominator() const { return denominator_; }

		bool simplify();
		
	private:
		void simplifyMinusSign() {
			if (numerator_ < 0 && denominator_ < 0)
				makePositive();
			else if (denominator_ < 0)
				moveMinusSignToNumerator();
		}
		void makePositive() {
			numerator_ = abs(numerator_);
			denominator_ = abs(denominator_);
		}
		void moveMinusSignToNumerator() {
			denominator_ = -denominator_;
			numerator_ = -numerator_;
		}

		long double numerator_{0};
		long long denominator_{1};
	};

	static ComputableLitteral makeAddition(const ComputableLitteral& rLitteral, const ComputableLitteral& lLitteral);

	static bool isInteger(const long double value) { return floor(value) == ceil(value); }
	static long long computeGreatestCommonDivisor(const long long value1, const long long value2);
};
