#include <iostream>

#include "helper/math.h"

int main() {
	double a = 0, b = 0, c = 0, discr = 0, x1 = 0, x2 = 0;

	while (!a) {
		std::cout << "Enter tree numbers(a,b,c), where a != 0: ";
		std::cin >> a >> b >> c;
		if (a == 0)
			std::cout << "Wrong input: \"a\" must be non-zero!\n";
	}
	discr = discriminant(a, b, c);
	if (discr < 0)
		std::cout << "The equation hasn't any roots!\n";
	else if (discr == 0) {
		double x1 = quadratic_equation_root(a, b, discr);
		std::cout << "The equation has one root: x1 = " << x1 << "\n";
	}
	else {
		double x1 = quadratic_equation_root(a, b, discr);
		double x2 = quadratic_equation_root(a, b, discr, math::Operation::MINUS);
		std::cout << "The equation has two roots: x1 = " << x1 << ", x2 = " << x2 << "\n";
	}
	

	return 0;
}
