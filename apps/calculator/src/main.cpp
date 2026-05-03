#include <iostream>
#include <stdexcept>
#include "calculator.hpp"

using namespace std;

int main() {
	try {
		ExpressionCalculator calc(7.14, -1.92, 4.41);
		calc.print();
	} catch (const exception& e) {
		cerr << "Помилка: " << e.what() << "\n";
	}

	return 0;
}