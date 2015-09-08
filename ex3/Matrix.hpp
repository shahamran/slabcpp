#ifndef _MATRIX_HPP
#define _MATRIX_HPP

#include <iostream>
#include <vector>
#include <thread>
#include "Complex.h"

#define DEFAULT_VALUE 0
#define DEFAULT_SIZE 1
#define PRINT_COLS_SEPARATOR '\t'
#define PRINT_ROWS_SEPARATOR std::endl

template <typename T>
class Matrix
{
public:

	class const_iterator
	{
	public:
		const_iterator(size_t row, size_t col) : _row(row), _col(col)
		{
		}

		const_iterator() : const_iterator(0, 0)
		{
		}

		const_iterator operator++(int a)
		{
			const_iterator old = *this;
			_increment();
			return old;
		}

		const_iterator operator++()
		{
			_increment();
			return *this;
		}

		const T* operator->()
		{
			return &_data[_row][_col];
		}

		const T& operator*()
		{
			return _data[_row][_col];
		}
	private:
		void _increment()
		{
			_col++;
			if (_col >= _cols)
			{
				_row++;
				_col = 0;
			}
		}
		size_t _row, _col;
	};

	typedef T value_type;
	typedef std::vector<T> MatRow; // A row in the matrix

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
		_data = std::vector<MatRow>(rows);
		for (size_t i = 0; i < rows; i++)
		{
			_data[i] = MatRow(cols, DEFAULT_VALUE);
		}
	}

	/**
	 * Constructs a default sized matrix (1x1).
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
		for (size_t i = 0; i < _rows; i++)
		{
			std::copy(rhs._data[i].begin(), rhs._data[i].end(), _data[i].begin());
		}
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

		}
		// Use matrix iterator do assign values.
		// TODO
		// ...
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
	const Matrix<T>& operator+(const Matrix<T>& rhs) const
	{
		if (_rows != rhs._rows || _cols != rhs._cols)
		{
			// Throw dimension exception
		}
		
		// Parellel / non-Parellel
	}

	/**
	 * Calculates the subtraction of another matrix from this one.
	 * @param rhs The matrix to subtract from this one, that satisfies: 
	 * rhs.rows() == this->rows() && rhs.cols() == this->cols()
	 * @return The result of subtraction matrix of the same dimensions).
	 */
	const Matrix<T>& operator-(const Matrix<T>& rhs) const
	{

		// Same
	}

	/**
	 * Multiply this matrix by a scalar.
	 * @param scalar The scalar to multiply this matrix by.
	 * @param mat The matrix to multiply.
	 * @return The result of the multiplication by scalar.
	 */
	friend const Matrix<T>& operator*(T scalar, const Matrix<T>& mat)
	{
		// Use iterator to multiply by scalar
	}

	/**
	 * Calculates the multiplication of this matrix by another.
	 * @param rhs A matrix that satisfies: rhs.rows() == this_matrix.cols()
	 * @return The result of the multiplication.
	 */
	const Matrix<T>& operator*(const Matrix<T>& rhs) const
	{
		if (_cols != rhs._rows)
		{
			// Throw exception
		}
		// Same
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
		return _data[row][col];
	}
	
	/**
	 * Gets a const reference of the value in the matrix in the specified cordinates.
	 * @param row The row number (0 to rows() - 1)
	 * @param col The column number (0 to cols() - 1)
	 * @return The matrix entry in the given cordinates (const reference).
	 */
	const T& operator()(size_t row, size_t col) const
	{
		return _data[row][col];
	}	
	
	/**
	 * @return The transpose of this matrix.
	 */
	const Matrix<T> trans() const
	{
		Matrix<T> result(_cols, _rows);
		for (size_t row = 0; row < _rows; row++)
		{
			for (size_t col = 0; col < _cols; col++)
			{
				result(col, row) = _data[row][col];
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
		for (size_t i = 0; i < _rows; i++)
		{
			result += _data[i][i];
		}
		return result;
	}
	
	/**
	 * Writes the matrix values to a given outstream in the following format:
	 * Every two columns are separated by PRINT_COLS_SEPARATOR ('\t').
	 * Every two line are separated by PRINT_ROWS_SEPARATOR (std::endl <=> '\n').
	 * (See MACROS).
	 * @param os The output stream to write to.
	 * @param mat The matrix to write.
	 */
	friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& mat)
	{
		for (size_t row = 0; row < mat._rows; row++)
		{
			for (size_t col = 0; col < mat._cols - 1; col++)
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
		return const_iterator();
	}

	const_iterator end()
	{
		return const_iterator(_rows, 0);
	}

private:
	
	void _addFirstHalf(const Matrix<T>& rhs)
	{

	}

	void _addSecondHalf(const Matrix<T>& rhs)
	{

	}

	size_t _rows, _cols;
	std::vector<MatRow> _data;
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
	for (size_t row = 0; row < _rows; row++)
	{
		for (size_t col = 0; col < _cols; col++)
		{
			result(col, row) = (*this)(row, col).conj();
		}
	}
	return result;
}

#endif