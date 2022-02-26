#pragma once
/*
	Matrix library

	Contains basic matrix functions.
*/


#include <iostream>
#include <vector>

class Matrix
{
	class Iterator {
	public:
		Iterator(double* ptr);
		Iterator(const double* ptr);
		Iterator(const Iterator&) = delete;
		Iterator& operator=(const Iterator&) = delete;
		double& operator[](size_t col);
		const double& operator[](size_t col) const;
	private:
		double* ptr_;
	};

	friend std::ostream& operator<<(std::ostream& out, const Matrix& value);
	friend std::istream& operator>>(std::istream& in, Matrix& value);
	friend bool operator==(const Matrix& op1, const Matrix& op2);
	friend bool operator!=(const Matrix& op1, const Matrix& op2);
public:

	Matrix(size_t row = 0, size_t column = 0);
	Matrix(size_t row, size_t column, std::vector<double> data);
	Matrix(const Matrix&) = default;
	Matrix& operator=(const Matrix&) = default;

	Matrix& operator+=(const Matrix& other);
	Matrix& operator-=(const Matrix& other);
	Matrix& operator*=(const Matrix& other);
	Matrix& operator*=(double value);
	Matrix& operator+=(double value);
	Matrix& operator-=(double value);
	Matrix& operator++();
	const Matrix operator++(int);
	Matrix& operator--();
	const Matrix operator--(int);
	Iterator operator[](size_t row);
	const Iterator operator[](size_t row) const;

	double& at(size_t row, size_t column);
	const double& at(size_t row, size_t column) const;
	bool isAdded(const Matrix& rhs)const;
	bool isMultiplied(const Matrix& rhs)const;
private:
	size_t row_;
	size_t column_;
	std::vector<double> data_;
};

const Matrix operator*(const Matrix& lhs, const Matrix& rhs);
const Matrix operator*(const Matrix& mat, double value);
const Matrix operator*(double value, const Matrix& mat);
const Matrix operator+(const Matrix& lhs, const Matrix& rhs);
const Matrix operator+(const Matrix& mat, double value);
const Matrix operator+(double value, const Matrix& mat);
const Matrix operator-(const Matrix& lhs, const Matrix& rhs);
const Matrix operator-(const Matrix& mat, double value);
const Matrix operator-(double value, const Matrix& mat);
std::ostream& operator<<(std::ostream& out, const Matrix& value);
std::istream& operator>>(std::istream& in, Matrix& value);
bool operator==(const Matrix& op1, const Matrix& op2);
bool operator!=(const Matrix& op1, const Matrix& op2);
