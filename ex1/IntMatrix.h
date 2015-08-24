#ifndef INT_MATRIX_H
#define INT_MATRIX_H

using namespace std;

#include <iostream>
#include <sstream>
#define INPUT_SEPARATOR ','

class IntMatrix
{
public:
	IntMatrix(size_t rows, size_t cols);
	IntMatrix(IntMatrix&& rvalue);
	IntMatrix(const IntMatrix &toCopy);
	IntMatrix();
	~IntMatrix();
	IntMatrix& operator=(IntMatrix other);
	IntMatrix operator+(const IntMatrix& other) const;
	IntMatrix& operator+=(const IntMatrix& other);
	IntMatrix operator*(const IntMatrix& other) const;
	IntMatrix operator*(int scalar) const;
	IntMatrix& operator*=(const IntMatrix& other);
	IntMatrix operator-(const IntMatrix& other) const;
	IntMatrix& operator-=(const IntMatrix& other);
	friend ostream& operator<<(ostream& out, const IntMatrix& mat);
	friend istream& operator>>(istream& in, IntMatrix& mat);
	IntMatrix& trans() const;
	int trace() const;

	bool canBeMultipliedBy(const IntMatrix& other) const
	{
		return (_cols == other._rows);
	}
	bool isSquare() const
	{
		return (_rows == _cols);
	}
	size_t getCols() const
	{
		return _cols;
	}
	size_t getRows() const
	{
		return _rows;
	}
private:
	size_t _rows, _cols;
	void swap(IntMatrix& toSwap);
	int** _data;
};


#endif
