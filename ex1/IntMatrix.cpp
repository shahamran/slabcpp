#include "IntMatrix.h"
#include <assert.h>
#define DEFAULT_SIZE 0
#define SEPARATOR " "
#define EMPTY_STRING ""

void IntMatrix::swap(IntMatrix& toSwap)
{
	std::swap(_data, toSwap._data);
	std::swap(_rows, toSwap._rows);
	std::swap(_cols, toSwap._cols);
	/*
	// Swap data
	int** tmpData = _data;
	_data = toSwap._data;
	toSwap._data = tmpData;
	// Swap dimensions
	size_t tmpRows = _rows, tmpCols = _cols;
	_rows = toSwap._rows;
	_cols = toSwap._cols;
	toSwap._rows = tmpRows;
	toSwap._cols = tmpCols;
	*/
	return;
}

IntMatrix::IntMatrix(size_t rows, size_t cols)
	: _rows(rows)
	, _cols(cols)
{
	assert(rows > 0 && cols > 0 || rows == cols == 0);
	if (rows == cols == 0)
	{
		_data = nullptr;
	}
	else
	{
		_data = new int*[rows];
		for (size_t i = 0; i < rows; i++)
		{
			_data[i] = new int[cols];
		}
	}
}

IntMatrix::IntMatrix(IntMatrix&& rvalue)
	: IntMatrix()
{
	swap(rvalue);
	return *this;
}

IntMatrix::IntMatrix(const IntMatrix& toCopy)
	: IntMatrix(toCopy._rows, toCopy._cols)
{
	for (size_t i = 0; i < toCopy._rows; i++)
	{
		for (size_t j = 0; j < toCopy._cols; j++)
		{
			this->_data[i][j] = toCopy._data[i][j];
		}
	}
}

IntMatrix::IntMatrix()
	: IntMatrix(DEFAULT_SIZE, DEFAULT_SIZE)
{
}

IntMatrix::~IntMatrix()
{
	if (_data != nullptr)
	{
		for (size_t i = 0; i < this->_rows;  i++)
		{
			delete[] _data[i];
		}
		delete[] _data;
	}
}

IntMatrix& IntMatrix::trans() const
{
	IntMatrix* result = new IntMatrix(_cols, _rows);
	for (size_t i = 0; i < _rows; i++)
	{
		for (size_t j = 0; j < _cols; j++)
		{
			result->_data[j][i] = this->_data[i][j];
		}
	}
	return *result;
}

int IntMatrix::trace() const
{
	int trace = 0;
	assert (_rows == _cols);
	// Assuming _rows == _cols
	for (size_t i = 0; i < _rows; i++)
	{
		trace += _data[i][i];
	}
	return trace;	
}

IntMatrix& IntMatrix::operator=(IntMatrix other)
{
	swap(other);
	return *this;
} // At this point, other is destroyed and *this lives carrying its values.

IntMatrix& IntMatrix::operator+(const IntMatrix& other) const
{
	IntMatrix* result = new IntMatrix(*this);
	*result += other;
	return *result;
}

IntMatrix& IntMatrix::operator+=(const IntMatrix& other)
{
	assert(_rows == other._rows && _cols == other._cols);
	for (size_t i = 0; i < _rows; i++)
	{
		for (size_t j = 0; j < _cols; j++)
		{
			this->_data[i][j] += other._data[i][j];
		}
	}
	return *this;
}

IntMatrix& IntMatrix::operator*(int scalar) const
{
	IntMatrix* result = new IntMatrix(*this);
	for (size_t i = 0; i < _rows; i++)
	{
		for (size_t j = 0; j < _cols; j++)
		{
			result->_data[i][j] *= scalar;
		}
	}
	return *result;
}

IntMatrix& IntMatrix::operator*(const IntMatrix& other) const
{
	IntMatrix* result = new IntMatrix(*this);
	*result *= other;
	return *result;
}

IntMatrix& IntMatrix::operator*=(const IntMatrix& other)
{
	assert(_cols == other._rows);
	IntMatrix tmp(this->_rows, other._cols);
	for (size_t i = 0; i < tmp._rows; i++)
	{
		for (size_t j = 0; j < tmp._cols; j++)
		{
			tmp._data[i][j] = 0;
			for (size_t k = 0; k < other._rows; j++)
			{
				tmp._data[i][j] += this->_data[i][k] * other._data[k][j];
			}
		}
	}
	swap(tmp);
	return *this;
} // Same trick as with the = operator, tmp is being deleted now.

IntMatrix& IntMatrix::operator-(const IntMatrix& other) const
{
	IntMatrix* result = new IntMatrix(*this);
	*result -= other;
	return *result;
}

IntMatrix& IntMatrix::operator-=(const IntMatrix& other)
{
	*this += (other * (-1));
	return *this;
}

ostream& operator<<(ostream& out, const IntMatrix& mat)
{
	for (size_t i = 0; i < mat._rows; i++)
	{
		for (size_t j = 0; j < mat._cols - 1; j++)
		{
			out << mat._data[i][j] << SEPARATOR;
		}
		out << mat._data[i][mat._cols - 1] << endl;
	}
	return out;
}

istream& operator>>(istream& in, IntMatrix& mat)
{
	string numStr;
	for (size_t i = 0; i < mat._rows; i++)
	{
		getline(in, numStr, ',');
		istringstream iss(numStr);
		for (size_t j = 0; j < mat._cols; j++)
		{
			iss >> mat._data[i][j];
		}
	}
	return in;
}