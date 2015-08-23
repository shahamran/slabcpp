#include "IntMatrix.h"
#include <assert.h>
#define DEFAULT_SIZE 1
#define SEPARATOR ','

void IntMatrix::swap(IntMatrix& toSwap)
{
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
	return;
}

IntMatrix::IntMatrix(size_t rows, size_t cols)
	: _rows(rows)
	, _cols(cols)
{
	_data = new int*[rows];
	for (size_t i = 0; i < rows; i++)
	{
		_data[i] = new int[cols];
	}
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
	for (size_t i = 0; i < this->_rows;  i++)
	{
		delete[] _data[i];
	}
	delete[] _data;
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
	// Assuming _rows == _cols
	for (size_t i = 0; i < _rows; i++)
	{
		trace += _data[i][i];
	}
	return trace;	
}

IntMatrix& IntMatrix::operator=(const IntMatrix& other)
{
	// Check if dimensions agree. If so, copy data.
	if (_rows == other._rows && _cols == other._cols)
	{
		for (size_t i = 0; i < _rows; i++)
		{
			for (size_t j = 0; j < _cols; j++)
			{
				_data[i][j] = other._data[i][j];
			}
		}
	}
	// If not, clone the other matrix and swap the clone with this.
	else
	{
		IntMatrix tmp(other);
		swap(tmp);
	}
	return *this;
} // At this point, tmp (which now has old 'this' members) is being deleted and freed :)

IntMatrix& IntMatrix::operator+(const IntMatrix& other) const
{
	IntMatrix* result = new IntMatrix(*this);
	*result += other;
	return *result;
}

IntMatrix& IntMatrix::operator+=(const IntMatrix& other)
{
	for (size_t i = 0; i < _rows; i++)
	{
		for (size_t j = 0; j < _cols; j++)
		{
			this->_data[i][j] += other._data[i][j];
		}
	}
	return *this;
}

IntMatrix& IntMatrix::operator*(const IntMatrix& other) const
{
	IntMatrix* result = new IntMatrix(*this);
	*result *= other;
	return *result;
}

IntMatrix& IntMatrix::operator*=(const IntMatrix& other)
{
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

ostream& operator<<(ostream& out, const IntMatrix& mat)
{
	
	for (size_t i = 0; i < mat._rows; i++)
	{
		for (size_t j = 0; j < mat._cols; j++)
		{
			out << mat._data[i][j] << " ";
		}
		out << endl;
	}
	return out;
}

istream& operator>>(istream& in, IntMatrix& mat)
{
	string numStr;
	for (size_t i = 0; i < mat._rows; i++)
	{
		getline(in, numStr, SEPARATOR);
		istringstream iss(numStr);
		for (size_t j = 0; j < mat._cols; j++)
		{
			iss >> mat._data[i][j];
		}
	}
	return in;
}