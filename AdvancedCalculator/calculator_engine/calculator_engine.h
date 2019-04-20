#pragma once

class CalculatorEngine
{
public:
	class ComputableLitteral {
		friend CalculatorEngine;

	public:
		explicit ComputableLitteral(const double value): value(value) {}
		ComputableLitteral() {};

	private:
		const double value{0};
	};

	static double makeAddition(const ComputableLitteral& rLitteral, const ComputableLitteral& lLitteral) { 
		return rLitteral.value + lLitteral.value;
	}
};
