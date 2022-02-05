#include "math.h"
#include <cmath>


double discriminant(double a, double b, double c)
{
	return sqr(b) - 4 * a * c;
}

double sqr(double n)
{
	return n * n;
}

double quadratic_equation_root(double a, double b, double discr, Operation op)
{
	/*if (discr == 0) {
		return (b) ? (-b / (2 * a)) : 0;
	}*/
	return (op == Operation::PLUS) ? (-b + std::sqrt(discr)) / (2 * a) : (-b - std::sqrt(discr)) / (2 * a);
}

double addition(double a, double b)
{
	return a + b;
}

double subtraction(double a, double b)
{
	return a - b;
}

double multiplication(double a, double b)
{
	return a * b;
}

double division(double a, double b)
{
	return a / b;
}

double root(double a, double b)
{	
	return (a < 0 && (int)b % 2) ? -pow(-a, 1/b) : pow(a, 1/b);
}

int factorial(int b)
{	
	if (!b || b==1)
		return 1;
	int result = 1;
	for (int i = 2; i < b+1; i++)
	{
		result *= i;
	}
	return result;
}

double mod(double a, double b) {
	double result = (int)(a / b);
	result = a - result * b;
	return result < 0 ? -result : result;
}


