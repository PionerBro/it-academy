#include "math.h"
#include <cmath>


double discriminant(double a, double b, double c)
{
	return sqr(b) - 4 * a * c;
}

double sqr(double n)
{
	return n*n;
}

double quadratic_equation_root(double a, double b, double discr, math::Operation op)
{
	if (discr == 0) {
		return (b) ? (-b / (2 * a)) : 0;
	}
	return (op == math::Operation::PLUS) ? (-b + std::sqrt(discr)) / (2 * a) : (-b - std::sqrt(discr)) / (2 * a);
}
