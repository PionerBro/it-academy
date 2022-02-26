#include "Matrix.h"

#include <algorithm>

Matrix::Iterator::Iterator(double* ptr) : ptr_(ptr) 
{
}

Matrix::Iterator::Iterator(const double* ptr) : ptr_(const_cast<double*>(ptr)) 
{
}

double& Matrix::Iterator::operator[](size_t col) {
	return *(ptr_ + col);
}

const double& Matrix::Iterator::operator[](size_t col) const {
	return *(ptr_ + col);
}

Matrix::Matrix(size_t row, size_t column) : row_(row), column_(column), data_(row * column)
{
	if (row_ && !column_)
		row_ = 0;
	else if (!row_ && column_)
		column_ = 0;
}

Matrix::Matrix(size_t row, size_t column, std::vector<double> data):Matrix(row, column)
{
	std::copy_n(data.begin(), std::min(data_.size(), data.size()), data_.begin());
}

Matrix::Iterator Matrix::operator[](size_t row) {
	return &data_[column_ * row];
}

const Matrix::Iterator Matrix::operator[](size_t row) const {
	return &data_[column_ * row];
}

Matrix& Matrix::operator+=(const Matrix& other)
{
	std::transform(data_.begin(), data_.end(), other.data_.begin(), data_.begin(), std::plus<double>());		
	return *this;
}

const Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
	Matrix tmp = lhs;
	tmp += rhs;
	return tmp;
}

Matrix& Matrix::operator-=(const Matrix& other)
{
	std::transform(data_.begin(), data_.end(), other.data_.begin(), data_.begin(), std::minus<double>());
	return *this;
}

const Matrix operator-(const Matrix& lhs, const Matrix& rhs) {
	Matrix tmp = lhs;
	tmp -= rhs;
	return tmp;
}

Matrix& Matrix::operator*=(const Matrix& other)
{
	Matrix tmp(row_, other.column_);
	for (size_t i = 0; i < row_; i++)
	{
		for (size_t j = 0; j < column_; ++j) {
			double sum = 0;
			for (size_t k = 0; k < other.row_; ++k) {
				sum += (*this)[i][k] * other[k][j];
			}
			tmp[i][j] = sum;
		}
	}
	*this = tmp;
	return *this;
}

const Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
	Matrix tmp = lhs;
	tmp *= rhs;
	return tmp;
}

Matrix& Matrix::operator*=(double value) {
	std::for_each(data_.begin(), data_.end(), [value](double& n) {n *= value; });
	return *this;
}

Matrix& Matrix::operator+=(double value) {
	std::for_each(data_.begin(), data_.end(), [value](double& n) {n += value; });
	return *this;
}

Matrix& Matrix::operator-=(double value) {
	std::for_each(data_.begin(), data_.end(), [value](double& n) {n -= value; });
	return *this;
}

const Matrix operator+(const Matrix& mat, double value) {
	Matrix tmp = mat;
	tmp += value;
	return tmp;
}

const Matrix operator+(double value, const Matrix& mat) {
	return mat + value;
}

const Matrix operator-(const Matrix& mat, double value) {
	Matrix tmp = mat;
	tmp -= value;
	return tmp;
}

const Matrix operator-(double value, const Matrix& mat) {
	return mat - value;
}

Matrix& Matrix::operator++() {
	std::for_each(data_.begin(), data_.end(), [](double& n) {++n; });
	return *this;
}

const Matrix Matrix::operator++(int) {
	Matrix tmp = *this;
	++(*this);
	return tmp;
}

Matrix& Matrix::operator--() {
	std::for_each(data_.begin(), data_.end(), [](double& n) {--n; });
	return *this;
}

const Matrix Matrix::operator--(int) {
	Matrix tmp = *this;
	--(*this);
	return tmp;
}


const Matrix operator*(const Matrix& mat, double value)
{
	Matrix tmp = mat;
	tmp *= value;
	return tmp;
}

const Matrix operator*(double value, const Matrix& mat)
{
	return mat * value;
}

std::ostream& operator<<(std::ostream& out, const Matrix& value)
{
	for (size_t i = 0; i < value.row_; ++i) {
		for (size_t j = 0; j < value.column_; ++j) {
			out << value[i][j] << " ";
		}
		out << "\n";
	}
	return out;
}

std::istream& operator>>(std::istream& in, Matrix& value) {
	Matrix tmp = value;
	for(auto& el : value.data_)
		in >> el;
	if (!in)
		value = tmp;
	return in;
}

double& Matrix::at(size_t row, size_t column) {
	return data_.at(row * column_ + column);
}

const double& Matrix::at(size_t row, size_t column) const {
	return data_.at(row * column_ + column);
}

bool Matrix::isAdded(const Matrix& rhs)const {
	return (row_ == rhs.row_ && column_ == rhs.column_);
}

bool Matrix::isMultiplied(const Matrix& rhs)const {
	return (column_ == rhs.row_);
}

bool operator==(const Matrix& lhs, const Matrix& rhs) {
	if (lhs.row_ != rhs.row_ || lhs.column_ != rhs.column_)
		return false;
	auto predicate = [](double p1, double p2) {
		return std::abs(p1 - p2) <= std::numeric_limits<double>::epsilon();
	};
	return std::equal(lhs.data_.begin(), lhs.data_.end(), rhs.data_.begin(), predicate);
}

bool operator!=(const Matrix& op1, const Matrix& op2) {
	return !(op1 == op2);
}


