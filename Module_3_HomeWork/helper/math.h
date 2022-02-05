#pragma once

/*
	Math library

	Contains popular math functions.
*/

enum class Operation {
	PLUS = 1,
	MINUS
};

// Returns discriminant
double discriminant(double a, double b, double c);
// Returns square
double sqr(double n);
// Returns roots of a quadratic equation
double quadratic_equation_root(double a, double b, double discr, Operation op = Operation::PLUS);
// Returns sum of two numbers
double addition(double a, double b);
// Returns difference of two numbers
double subtraction(double a, double b);
// Returns product of two numbers
double multiplication(double a, double b);
// Returns quotient of two numbers
double division(double a, double b);
// Returns b-th root of a number 'a'
double root(double a, double b);
// Returns remainder after division two numbers
double mod(double a, double b);
// Returns factorial of an integer
int factorial(int b);

