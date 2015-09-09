#ifndef _MATRIX_HPP
#define _MATRIX_HPP

#include <iostream>
#include <vector>
#include <thread>
#include "Complex.h"
#include "MatrixExceptions.hpp"

#define DEFAULT_VALUE 0
#define DEFAULT_SIZE 1
#define MINIMAL_SIZE 1
#define PRINT_COLS_SEPARATOR '\t'
#define PRINT_ROWS_SEPARATOR std::endl

template <typename T>
class Matrix
{
public:
	typedef T value_type;
	typedef std::vector<T> MatData;
	typedef MatData::const_iterator const_iterator;

	/**
	 * Swaps the internal members of one matrix with another.
	 */
	friend void swap(Matrix<T>& mat, Matrix<T>& other)
	{
		std::swap(mat._rows, other._rows);
		std::swap(mat._cols, other._cols);
		std::swap(mat._data, other._data);
		return;
	}

	/**
	 * Constructs a matrix with the given dimensions and default values (0).
	 * @param rows The number of rows
	 * @param cols The number of columns
	 */
	Matrix(size_t rows, size_t cols) :
		_rows(rows), _cols(cols)
	{
		// make sure matrix dimensions are positive
		if (rows < MINIMAL_SIZE || cols < MINIMAL_SIZE)
		{
			// Throw exception
		}
		_data = MatData(rows * cols, DEFAULT_VALUE);
	}

	/**
	 * Constructs a default sized matrix (1x1) with default value (0).
	 */
	Matrix() : Matrix<T>(DEFAULT_SIZE, DEFAULT_SIZE)
	{
	}

	/**
	 * Deep copy constructor for a given matrix.
	 * @param rhs The matrix to copy.
	 */
	Matrix(const Matrix<T>& rhs) :
		Matrix<T>(rhs._rows, rhs._cols)
	{
		std::copy(rhs._data.begin(), rhs._data.end(), _data.begin());
	}

	/**
	 * Move constructor. 'Steals' the given matrix values.
	 * @param rvalue The matrix to get values from.
	 */
	Matrix(Matrix<T> && rvalue) :
		Matrix<T>()
	{
		swap(*this, rvalue);
	}

	/**
	 * Creates a matrix with the given dimensions and the values set by the given vector.
	 * @param rows The number of rows.
	 * @param cols The number of columns.
	 * @param cells A vector of values to assign to this matrix that satisfies: 
	 * cells.size() == rows * cols.
	 */
	Matrix(size_t rows, size_t cols, const std::vector<T>& cells) :
		Matrix<T>(rows, cols)
	{
		if ((rows * cols) != cells.size())
		{
			// Throw exception
		}
		std::copy(cells.begin(), cells.end(), _data.begin());
	}

	/**
	 * Destructor for a matrix.
	 */
	~Matrix()
	{
	}

	/**
	 * Change this matrix to be the same as another.
	 * Note that this method takes parameters by value which are copied using the
	 * move / copy constructor thus making it more efficient.
	 * @param rhs The matrix to assign.
	 * @return a reference to the freshly changed matrix.
	 */
	Matrix<T>& operator=(Matrix<T> rhs)
	{
		swap(*this, rhs);
		return *this;
	}

	/**
	 * Calculates the addition of another matrix to this one.
	 * @param rhs The matrix to add to this one, that satisfies: 
	 * rhs.rows() == this->rows() && rhs.cols() == this->cols()
	 * @return The result of addition (matrix of the same dimensions).
	 */
	const Matrix<T> operator+(const Matrix<T>& rhs) const
	{
		if (_rows != rhs._rows || _cols != rhs._cols)
		{
			throw bad_addition();
		}
		Matrix<T> result(*this);
		/*if (_isParallel)
		{
			_multithreadAddition(result, rhs);
		}
		else
		{
			for (size_t row = 0; row < _rows; ++row)
			{
				_addRow(result._data[row], rhs._data[row]);
			}
		}*/
		return result;
	}

	/**
	 * Calculates the subtraction of another matrix from this one.
	 * @param rhs The matrix to subtract from this one, that satisfies: 
	 * rhs.rows() == this->rows() && rhs.cols() == this->cols()
	 * @return The result of subtraction matrix of the same dimensions).
	 */
	const Matrix<T> operator-(const Matrix<T>& rhs) const
	{
		if (_rows != rhs._rows || _cols != rhs._cols)
		{
			throw bad_addition();
		}
		Matrix<T> result(*this);/*
		if (_isParallel)
		{
			_multithreadAddition(result, rhs, false);
		}
		else
		{
			for (size_t row = 0; row < _rows; ++row)
			{
				_addRow(result._data[row], rhs._data[row], false);
			}
		}*/
		return result;
	}

	/**
	 * Calculates the multiplication of this matrix by another.
	 * @param rhs A matrix that satisfies: rhs.rows() == this_matrix.cols()
	 * @return The result of the multiplication.
	 */
	const Matrix<T> operator*(const Matrix<T>& rhs) const
	{
		if (_cols != rhs._rows)
		{
			// Throw exception
		}
		Matrix<T> result(_rows, rhs._cols);
		// Same
		return result;
	}

	/**
	 * Checks if this matrix is identical to another.
	 * @param rhs The matrix to compare to.
	 * @return true if the matrices are identical, false otherwise.
	 */
	bool operator==(const Matrix<T>& rhs) const
	{
		if (_rows != rhs._rows || _cols != rhs._cols)
		{
			return false;
		}
		// Use iterator to check equiality
	}
	
	/**
	 * @param rhs The matrix to compare to.
	 * @return !(*this == rhs) (see operator==)
	 */
	bool operator!=(const Matrix<T>& rhs) const
	{
		return !operator==(rhs);
	}
	
	/**
	 * Gets the value in the matrix in the specified cordinates.
	 * @param row The row number (0 to rows() - 1)
	 * @param col The column number (0 to cols() - 1)
	 * @return The matrix entry in the given cordinates.
	 */
	T& operator()(size_t row, size_t col)
	{
		return _data[row * _cols + col];
	}
	
	/**
	 * Gets a const reference of the value in the matrix in the specified cordinates.
	 * @param row The row number (0 to rows() - 1)
	 * @param col The column number (0 to cols() - 1)
	 * @return The matrix entry in the given cordinates (const reference).
	 */
	const T& operator()(size_t row, size_t col) const
	{
		return _data[row * _cols + col];
	}	
	
	/**
	 * @return The transpose of this matrix.
	 */
	const Matrix<T> trans() const
	{
		Matrix<T> result(_cols, _rows);
		for (size_t row = 0; row < _rows; ++row)
		{
			for (size_t col = 0; col < _cols; ++col)
			{
				result(col, row) = (*this)(row, col);
			}
		}
		return result;
	}
	
	/**
	 * Calculates the trace of this matrix, if it is square.
	 * @return sum(A(i,i)) for 0 <= i < rows.
	 * @throws 
	 */
	T trace() const
	{
		if (_rows != _cols)
		{
			// throw exception
		}
		T result(0);
		for (size_t i = 0; i < _rows; ++i)
		{
			result += (*this)(i, i);
		}
		return result;
	}
	
	/**
	 * Writes the matrix values to a given outstream in the following format:
	 * Every two columns are separated by PRINT_COLS_SEPARATOR ('\t').
	 * Every two line are separated by PRINT_ROWS_SEPARATOR (std::endl - new line).
	 * (See MACROS).
	 * @param os The output stream to write to.
	 * @param mat The matrix to write.
	 */
	friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& mat)
	{
		for (size_t row = 0; row < mat._rows; ++row)
		{
			for (size_t col = 0; col < mat._cols - 1; ++col)
			{
				os << mat(row, col) << PRINT_COLS_SEPARATOR;
			}
			os << mat(row, mat._cols - 1) << PRINT_ROWS_SEPARATOR;
		}
		return os;
	}
	
	/**
	 * @return The number of rows in this matrix.
	 */
	size_t rows() const
	{
		return _rows;
	}

	/**
	 * @return The number of columns in this matrix.
	 */
	size_t cols() const
	{
		return _cols;
	}

	const_iterator begin()
	{
		return _data.begin();
	}

	const_iterator end()
	{
		return _data.end();
	}

	bool isSquareMatrix()
	{
		return _cols == _rows;
	}

	void setParallel(bool isParallel)
	{
		_isParallel = isParallel;
	}

private:/*
	static void _addRow(MatRow& row1, const MatRow& row2, bool add = true)
	{
		if (add)
		{
			for (size_t i = 0; i < row1.size(); ++i)
			{
				row1[i] += row2[i];
			}
		}
		else
		{
			for (size_t i = 0; i < row1.size(); ++i)
			{
				row1[i] -= row2[i];
			}
		}
		
	}

	void _multithreadAddition(Matrix<T>& mat, const Matrix<T>& other, bool add = true) const
	{
		std::vector<std::thread> threads(_rows);
		for (size_t row = 0; row < _rows; ++row)
		{
			threads[row] = std::thread(_addRow, std::ref(mat._data[row]), std::ref(other._data[row]), add);
		}
		for (size_t row = 0; row < _rows; ++row)
		{
			threads[row].join();
		}
	}*/

	bool _isParallel;
	size_t _rows, _cols;
	MatData _data;
};

/**
 * A specialized transpoe method.
 * When called with a complex matrix, returns the hermitian transpose matrix of this one.
 * The result <A*> satisfies: for evey 0 <= i < rows, 0 <= j < cols: A*(i,j) = A(j,i).conj()
 * @return The conjugate transpose of this matrix.
 */
template<>
const Matrix<Complex> Matrix<Complex>::trans() const
{
	Matrix<Complex> result(_cols, _rows);
	for (size_t row = 0; row < _rows; ++row)
	{
		for (size_t col = 0; col < _cols; ++col)
		{
			result(col, row) = (*this)(row, col).conj();
		}
	}
	return result;
}

#endif