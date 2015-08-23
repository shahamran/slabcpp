#ifndef INT_MATRIX_H
#define INT_MATRIX_H

using namespace std;

#include <iostream>

class IntMatrix
{
public:
	IntMatrix(size_t rows, size_t cols);
	IntMatrix(const IntMatrix &toCopy);
	IntMatrix();
	~IntMatrix();
	IntMatrix& operator=(const IntMatrix& other);
	IntMatrix& operator+(const IntMatrix& other) const;
	IntMatrix& operator+=(const IntMatrix& other);
	IntMatrix& operator*(const IntMatrix& other) const;
	IntMatrix& operator*=(const IntMatrix& other);
	friend ostream& operator<<(ostream& out, const IntMatrix& mat);
	friend istream& operator>>(istream& in, IntMatrix& mat);
	IntMatrix trans(const IntMatrix& toTrans) const;
	int trace() const;

private:
	size_t _rows, _cols;
	void swap(IntMatrix& toSwap);
	int** _data;
};


#endif
