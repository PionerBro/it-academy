#pragma once

/*
	Math library

	Contains popular math functions.
*/

namespace math {
	enum class Operation {
		PLUS = 1,
		MINUS
	};
}

// Returns discriminant
double discriminant(double a, double b, double c);
// Returns square
double sqr(double n);
// Returns roots of a quadratic equation
double quadratic_equation_root(double a, double b, double discr, math::Operation op = math::Operation::PLUS);
