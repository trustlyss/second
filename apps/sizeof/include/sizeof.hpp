#pragma once

#include <iostream>
#include <cmath>
#include <stdexcept>

using namespace std;



class ExpressionCalculator {
private:
	double a, b, x;

	double numerator() const {
		return pow(x, 3.0 / 4.0) - a * x;   // ⁴√x³ − a·x
	}

	double denominator() const {
		return log10(x) + b;                  // log₁₀(x) + b
	}

public:
	ExpressionCalculator(double a, double b, double x)
		: a(a), b(b), x(x) {}

	double calculate() const {
		if (x <= 0)
			throw invalid_argument("x має бути > 0");

		double den = denominator();
		if (den == 0.0)
			throw runtime_error("Ділення на нуль (знаменник = 0)");

		return numerator() / den;
	}

	void print() const {
		cout << "a = " << a << ", b = " << b << ", x = " << x << "\n";
		cout << "numerator : " << numerator()   << "\n";
		cout << "denominator : " << denominator() << "\n";
		cout << "Result : " << calculate()   << "\n";
	}
};