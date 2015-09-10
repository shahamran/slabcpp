#ifndef _MATRIX_HPP
#define _MATRIX_HPP

#include <iostream>
#include <vector>
#include <thread>
#include <cassert>
#include <functional>
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
	typedef typename MatData::const_iterator const_iterator;
	typedef typename MatData::iterator iterator;

	/**
	 * Swaps the internal members of one matrix with another.
	 */
	friend void swap(Matrix& mat, Matrix& other)
	{
		std::swap(mat._rows, other._rows);
		std::swap(mat._cols, other._cols);
		std::swap(mat._data, other._data);
		return;
	}

	/**
	 * Constructs a matrix with the given dimensions and default values (0).
	 * Note that this method is MORE efficient than creating an empty vector and
	 * then pushing elements to it.
	 * @param rows The number of rows
	 * @param cols The number of columns
	 */
	Matrix(size_t rows, size_t cols) :
		_rows(rows), _cols(cols)
	{
		// make sure matrix dimensions are positive or both 0 (< MINIMAL_SIZE)
		if (rows < MINIMAL_SIZE && cols < MINIMAL_SIZE)
		{	// Create an empty matrix
			_data = MatData();
		}
		else if (rows < MINIMAL_SIZE || cols < MINIMAL_SIZE)
		{	// Throw an exception
			throw non_positive();
		}
		else
		{	// Create a vector with the given size with default values
			_data = MatData(rows * cols, DEFAULT_VALUE);
		}		
	}

	/**
	 * Constructs a default sized matrix (1x1) with default value (0).
	 */
	Matrix() : 
		Matrix(DEFAULT_SIZE, DEFAULT_SIZE)
	{
	}

	/**
	 * Deep copy constructor for a given matrix.
	 * @param rhs The matrix to copy.
	 */
	Matrix(const Matrix& rhs) :
		Matrix(rhs._rows, rhs._cols)
	{
		std::copy(rhs._data.begin(), rhs._data.end(), _data.begin());
	}

	/**
	 * Move constructor. 'Steals' the given matrix values.
	 * @param rvalue The matrix to get values from.
	 */
	Matrix(Matrix && rvalue) :
		Matrix()
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
	Matrix(size_t rows, size_t cols, const MatData& cells) :
		Matrix(rows, cols)
	{
		if ((rows * cols) != cells.size())
		{
			throw no_match(MatDimensions(rows, cols), MatDimensions(1, cells.size()));
		}
		// Copy the data to the matrix.
		std::copy(cells.begin(), cells.end(), _data.begin());
	}

	/**
	 * Change this matrix to be the same as another.
	 * Note that this method takes parameters by value which are copied using the
	 * move / copy constructor thus making it more efficient.
	 * @param rhs The matrix to assign.
	 * @return a reference to the freshly changed matrix.
	 */
	Matrix& operator=(Matrix rhs)
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
	const Matrix operator+(const Matrix& rhs) const
	{
		if (_rows != rhs._rows || _cols != rhs._cols)
		{
			throw bad_addition(MatDimensions(_rows, _cols), MatDimensions(rhs._rows, rhs._cols));
		}
		Matrix result(*this);
		if (s_isParallel)
		{
			_multithreadAddition(result, rhs);
		}
		else
		{
			auto dest_it = result._data.begin();
			auto src_it = rhs._data.cbegin();
			for (; dest_it != result._data.end(); ++dest_it, ++src_it)
			{
				*dest_it += *src_it;
			}
		}
		return result;
	}

	/**
	 * Calculates the subtraction of another matrix from this one.
	 * @param rhs The matrix to subtract from this one, that satisfies: 
	 * rhs.rows() == this->rows() && rhs.cols() == this->cols()
	 * @return The result of subtraction matrix of the same dimensions).
	 */
	const Matrix operator-(const Matrix& rhs) const
	{
		if (_rows != rhs._rows || _cols != rhs._cols)
		{
			throw bad_addition(MatDimensions(_rows, _cols), MatDimensions(rhs._rows, rhs._cols));
		}
		Matrix result(*this);
		if (s_isParallel)
		{
			_multithreadAddition(result, rhs, false);
		}
		else
		{
			auto dest_it = result._data.begin();
			auto src_it = rhs._data.cbegin();
			for (; dest_it != result._data.end(); ++dest_it, ++src_it)
			{
				*dest_it -= *src_it;
			}
		}
		return result;
	}

	/**
	 * Calculates the multiplication of this matrix by another.
	 * @param rhs A matrix that satisfies: rhs.rows() == this_matrix.cols()
	 * @return The result of the multiplication.
	 */
	const Matrix operator*(const Matrix& rhs) const
	{
		if (_cols != rhs._rows)
		{
			throw bad_multiplication(MatDimensions(_rows, _cols), 
									 MatDimensions(rhs._rows, rhs._cols));
		}
		Matrix result(_rows, rhs._cols);
		if (s_isParallel)
		{
			_multithreadedMultiplication(result, rhs);
		}
		else
		{
			for (size_t i = 0; i < _rows; ++i)
			{
				for (size_t j = 0; j < rhs._cols; ++j)
				{
					for (size_t k = 0; k < _cols; ++k)
					{
						result(i, j) += (*this)(i, k) * rhs(k, j);
					}
				}
			}
		}
		return result;
	}

	/**
	 * Checks if this matrix is identical to another.
	 * @param rhs The matrix to compare to.
	 * @return true if the matrices are identical, false otherwise.
	 */
	bool operator==(const Matrix& rhs) const
	{
		if (_rows != rhs._rows || _cols != rhs._cols)
		{
			return false;
		}
		// Use iterator to check equiality
		assert(rhs._data.size() == _data.size());
		auto it = rhs._data.begin(),
		     my_it  = _data.begin();
		for (; it != rhs._data.end(); ++it, ++my_it)
		{
			if (*my_it != *it)
			{
				return false;
			}
		}
		return true;
	}
	
	/**
	 * @param rhs The matrix to compare to.
	 * @return !(*this == rhs) (see operator==)
	 */
	bool operator!=(const Matrix& rhs) const
	{
		return !(*this == rhs);
	}
	
	/**
	 * Gets the value in the matrix in the specified cordinates.
	 * @param row The row number (0 to rows() - 1)
	 * @param col The column number (0 to cols() - 1)
	 * @return The matrix entry in the given cordinates.
	 */
	T& operator()(size_t row, size_t col)
	{
		if (row >= _rows || col >= _cols)
		{
			throw matrix_index_out_of_range(MatDimensions(_rows, _cols), MatDimensions(row, col));
		}
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
		if (row >= _rows || col >= _cols)
		{
			throw matrix_index_out_of_range(MatDimensions(_rows, _cols), MatDimensions(row, col));
		}
		return _data[row * _cols + col];
	}	
	
	/**
	 * @return The transpose of this matrix.
	 */
	const Matrix trans() const
	{
		Matrix result(_cols, _rows);
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
			throw bad_trace(MatDimensions(_rows, _cols));
		}
		T result(DEFAULT_VALUE);
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
	friend std::ostream& operator<<(std::ostream& os, const Matrix& mat)
	{
		for (size_t row = 0; row < mat._rows; ++row)
		{
			for (size_t col = 0; col < mat._cols; ++col)
			{
				os << mat(row, col) << PRINT_COLS_SEPARATOR;
			}
			os << PRINT_ROWS_SEPARATOR;
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

	static void setParallel(bool isParallel)
	{
		if (isParallel != s_isParallel)
		{
			s_isParallel = isParallel;
			std::string msg = isParallel ? "parallel" : "non-parallel";
			std::cout << "Generic Matrix mode changed to " << msg << " mode." << std::endl;
		}
	}

private:

	static void _multiplyRow(Matrix& dest, const Matrix& lhs, const Matrix& rhs, size_t i)
	{
		for (size_t j = 0; j < rhs._cols; ++j)
		{
			for (size_t k = 0; k < lhs._cols; ++k)
			{
				dest(i, j) += lhs(i, k) * rhs(k, j);
			}
		}
	}

	void _multithreadedMultiplication(Matrix& dest, const Matrix& rhs) const
	{
		std::vector<std::thread> threads(dest._rows);
		for (size_t row = 0; row < dest._rows; ++row)
		{
			threads[row] = std::thread(_multiplyRow,
									   std::ref(dest),
									   std::cref(*this),
									   std::cref(rhs), row);
		}
		for (size_t row = 0; row < _rows; ++row)
		{
			threads[row].join();
		}
	}

	static void _addRow(Matrix& dest, const Matrix& rhs, size_t row, bool add = true)
	{
		if (add)
		{
			for (size_t i = 0; i < dest._cols; ++i)
			{
				dest(row, i) += rhs(row, i);
			}
		}
		else
		{
			for (size_t i = 0; i < dest._cols; ++i)
			{
				dest(row, i) -= rhs(row, i);
			}
		}		
	}

	void _multithreadAddition(Matrix& dest, const Matrix& rhs, bool add = true) const
	{
		std::vector<std::thread> threads(dest._rows);
		for (size_t row = 0; row < dest._rows; ++row)
		{
			threads[row] = std::thread(_addRow,
									   std::ref(dest),
									   std::cref(rhs), row, add);
		}
		for (size_t row = 0; row < _rows; ++row)
		{
			threads[row].join();
		}
	}

	static bool s_isParallel;
	size_t _rows, _cols;
	MatData _data;
};

template <typename T>
bool Matrix<T>::s_isParallel = false;

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