#include "IntMatrix.h"
#include <assert.h>


#define DEFAULT_SIZE 0
#define PRINT_SEPARATOR " "
#define EMPTY_STRING ""

/**
* A swap function that replaces this matrix's internal members with the other matrix.
*
* @param toSwap The matrix to be swapped with.
*/
void IntMatrix::swap(IntMatrix& toSwap)
{
	std::swap(_data, toSwap._data);
	std::swap(_rows, toSwap._rows);
	std::swap(_cols, toSwap._cols);
	return;
}

/**
* The most basic constructor for an IntMatrix object.
* Allocates a dynamic 2d array of ints (int** _data).
*
* @param rows The number of rows in this matrix
* @param cols The number of columns in this matrix
*/
IntMatrix::IntMatrix(size_t rows, size_t cols)
	: _rows(rows)
	, _cols(cols)
{
	assert(~((rows == 0) ^ (cols == 0))); // Make sure rows,cols > 0 OR rows = cols = 0
	if (rows == 0)
	{
		_data = nullptr;
	}
	else
	{   // Allocates a dynamic 2d array of ints.
		_data = new int*[rows];
		for (size_t i = 0; i < rows; i++)
		{
			_data[i] = new int[cols];
		}
	}
}

/**
* A shallow-copy constructor that steals the allocated data from the given
* rvalue IntMatrix.
*
* @param rvalue An rvalue IntMatrix object.
*/
IntMatrix::IntMatrix(IntMatrix&& rvalue)
	: IntMatrix()
{
	swap(rvalue);
}

/**
* A deep-copy constructor that creates a new independent data array which is a copy of
* the given IntMatrix.
*
* @param toCopy The IntMatrix object to copy.
*/
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

/**
* Default constructor for IntMatrix. Constructs an IntMatrix with 0 rows
* and 0 columnts (meaning no memory is allocated for the _data array).
*/
IntMatrix::IntMatrix()
	: IntMatrix(DEFAULT_SIZE, DEFAULT_SIZE)
{
}

/**
* Destructor for IntMatrix object. Deletes all data allocated to this matrix.
*/
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

/**
* The assignment operator. This IntMatrix will have the same values as the copied one.
*
* @param other The IntMatrix to copy.
*/
IntMatrix& IntMatrix::operator=(IntMatrix other)
{
	swap(other); // Other is passed by value, no harm done.
	return *this;
} // At this point, other is destroyed and *this lives carrying its values.

/**
* Calculates the addition of another matrix to this one.
* Only call with a matrix that has the same dimensions as this one.
*
* @param other A matrix with the same dimensions as this one to add.
* @return An IntMatrix which is the result of the addition.
*/
IntMatrix IntMatrix::operator+(const IntMatrix& other) const
{
	IntMatrix result = IntMatrix(*this);
	result += other;
	return result;
}

/**
* Adds a matrix to this one.
* Only call with another matrix with the same dimensions.
*
* @param other Another IntMatrix with the same dimensions.
*/
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

/**
* Calculates the product of multiplication of this matrix by another one.
* Only call with a matrix that satisfy (this->_cols == other._rows).
*
* @param other Another matrix with the right dimensions (see above).
* @return The matrix multiplication result.
*/
IntMatrix IntMatrix::operator*(int scalar) const
{
	IntMatrix result = IntMatrix(*this);
	for (size_t i = 0; i < _rows; i++)
	{
		for (size_t j = 0; j < _cols; j++)
		{
			result._data[i][j] *= scalar;
		}
	}
	return result;
}

/**
* Calculates the multiplication of this matrix by a scalar (integer).
*
* @param scalar The scalar by which the matrix will be multiplied
* @return The result of the multiplication by scalar.
*/
IntMatrix IntMatrix::operator*(const IntMatrix& other) const
{
	IntMatrix result = IntMatrix(*this);
	result *= other;
	return result;
}

/**
* Multiplies this matrix by another.
*
* @param other The matrix by which this matrix will be multiplied
*/
IntMatrix& IntMatrix::operator*=(const IntMatrix& other)
{
	assert(_cols == other._rows);
	IntMatrix tmp(this->_rows, other._cols);
	for (size_t i = 0; i < tmp._rows; i++)
	{
		for (size_t j = 0; j < tmp._cols; j++)
		{
			tmp._data[i][j] = 0;
			for (size_t k = 0; k < other._rows; k++)
			{
				tmp._data[i][j] += this->_data[i][k] * other._data[k][j];
			}
		}
	}
	swap(tmp);
	return *this;
} // Same trick as with the = operator, tmp is being deleted now.

/**
 * Calculates the subtraction of another matrix from this one.
 * Only call with a matrix that has the same dimensions as this one.
 *
 * @param other A matrix with the same dimensions as this one to subtact.
 * @return An IntMatrix which is the result of the subtraction.
 */
IntMatrix IntMatrix::operator-(const IntMatrix& other) const
{
	IntMatrix result = IntMatrix(*this);
	result -= other;
	return result;
}

/**
* Subtracts a matrix from this one.
* Only call with another matrix with the same dimensions.
*
* @param other Another IntMatrix with the same dimensions.
*/
IntMatrix& IntMatrix::operator-=(const IntMatrix& other)
{
	*this += (other * (-1)); // Just add ((-1) * other) to this matrix.
	return *this;
}

/**
* 'Prints' this matrix to a given out-stream.
* Writing is done in the following format:
* Each matrix entry is followed by a space character except the last one in the line.
* Every two lines are separated by a single newline ('\n') char.
*
* @param out An output stream object
* @param mat The IntMatrix object reference.
*/
ostream& operator<<(ostream& out, const IntMatrix& mat)
{
	assert(~((mat._rows == 0) ^ (mat._cols == 0))); // (rows == cols) == 0 OR rows, cols > 0
	if (mat._rows == 0)
	{ // The empty matrix output is just a blank line!
		out << endl;
		return out;
	}
	for (size_t i = 0; i < mat._rows; i++)
	{
		for (size_t j = 0; j < mat._cols - 1; j++)
		{
			out << mat._data[i][j] << PRINT_SEPARATOR; // PRINT_SEPARATOR is a space
		}
		out << mat._data[i][mat._cols - 1] << endl; // The last entry isn't followed by a space.
	}
	return out;
}

/**
* Gets a given matrix's values from a given input-stream.
* The input is done in the following format:
* Each line in the input is a line of matrix entries.
* Every entry is followed by a single comma (',') character.
* Make sure the number of rows and columns in the input match the given matrix's dimensions.
*
* @param in The input-stream
* @param mat The matrix to assign.
*/
istream& operator>>(istream& in, IntMatrix& mat)
{
	string numStr;
	size_t a, b;
	for (size_t i = 0; i < mat._rows; i++)
	{
		a = 0; b = 0;
		in >> numStr; // Gets a line of input.
		for (size_t j = 0; j < mat._cols; j++)
		{
			b = numStr.find(INPUT_SEPARATOR, a); // Find the index of a comma
			istringstream(numStr.substr(a, b - a)) >> mat._data[i][j]; // Extract the number
			a = b + 1; // Move to the next point after the comma
		} // Do that <_cols> times
	}
	return in;
}

/**
* @return The transpose of this matrix.
*/
IntMatrix IntMatrix::trans() const
{
	IntMatrix result = IntMatrix(_cols, _rows);
	for (size_t i = 0; i < _rows; i++)
	{
		for (size_t j = 0; j < _cols; j++)
		{
			result._data[j][i] = this->_data[i][j];
		}
	}
	return result;
}

/**
* Make sure this matrix is square before using this function.
* The check can be done by the isSquare() function.
*
* @return The trace of this matrix.
*/
int IntMatrix::trace() const
{
	int trace = 0;
	assert(_rows == _cols);
	// Assuming _rows == _cols
	for (size_t i = 0; i < _rows; i++)
	{
		trace += _data[i][i];
	}
	return trace;
}