#ifndef _MATRIX_HPP
#define _MATRIX_HPP

// --------------------------- includes -----------------------------
#include <iostream>	// cout
#include <vector>
#include <thread>	// multi-threading
#include <cassert>
#include <functional>	// 
#include "Complex.h"
#include "MatrixExceptions.hpp"

// --------------------------- MACROS -------------------------------
#define DEFAULT_VALUE 0 // Default matrix entries value
#define DEFAULT_SIZE 1
#define MINIMAL_SIZE 1
#define PRINT_COLS_SEPARATOR '\t'
#define PRINT_ROWS_SEPARATOR std::endl

// ------------------------ class definition ------------------------
/**
 * This class represents a generic matrix object that can contain every element T
 * that supports: operators +, +=, -, -=, *, =, ==, !=, <<
 * and a constructor that takes 0 as an argument (T(0) compiles and runs).
 */
template <typename T>
class Matrix
{
public:
	/**
	 * MatData is a vector of T elements which represents the matrix data.
	 * since the data is saved in one vector, the const_iterator and iterator
	 * are just forwarded to the vector, thus giving us random-access iterators
	 * (which are bidirectional-iterators++)
	 */
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

	// ----------------------- constructors -------------------------

	/**
	 * Constructs a matrix with the given dimensions and default values (0).
	 * Efficiency note: this method is MORE efficient than creating an empty vector and
	 * then pushing elements into it (or not specifying the default value)
	 * @param rows The number of rows
	 * @param cols The number of columns
	 * @throw non_positive if non-positive value is given to exactly one of the dimensions
	 * (row / col) this exception is thrown.
	 * @throw bad_alloc this is thrown if memory for the matrix could not be allocated
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
	 * @throw non_positive if non-positive value is given to exactly one of the dimensions
	 * (row / col) this exception is thrown.
	 * @throw bad_alloc this is thrown if memory for the matrix could not be allocated
	 */
	Matrix() : 
		Matrix(DEFAULT_SIZE, DEFAULT_SIZE)
	{
	}

	/**
	 * Deep copy constructor for a given matrix.
	 * @param rhs The matrix to copy.
	 * @throw bad_alloc this is thrown if memory for the matrix could not be allocated
	 */
	Matrix(const Matrix& rhs) :
		Matrix(rhs._rows, rhs._cols)
	{
		std::copy(rhs._data.begin(), rhs._data.end(), _data.begin());
	}

	/**
	 * Move constructor. 'Steals' the given matrix values.
	 * @param rvalue The matrix to get values from.
	 * @throw bad_alloc it is unlikely, but this exception can be thrown if memory for a 1x1 
	 * matrix can't be allocated.
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
	 * @throw non_positive if non-positive value is given to exactly one of the dimensions
	 * (row / col) this exception is thrown.
	 * @throw bad_alloc this is thrown if memory for the matrix could not be allocated
	 * @throw no_match if the given matrix dimensions don't match the given vector's size,
	 * i.e cells.size() != rows * cols
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

	// -------------------- operators -------------------------------

	/**
	 * Change this matrix to be the same as another.
	 * Note that this method takes parameters by value which are copied using the
	 * move / copy constructor thus making it more efficient.
	 * shouldn't throw exceptions, maybe when calling the copy constructor for the
	 * by-value copying.
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
	 * @throw bad_addition In case the matrix dimensions don't fit, a bad_addition
	 * exception is thrown.
	 * @throw bad_alloc this is thrown if memory for the result matrix could not be allocated
	 */
	const Matrix operator+(const Matrix& rhs) const
	{
		Matrix result(*this);
		_addOrSubtract(result, rhs);
		return result;
	}

	/**
	 * Calculates the subtraction of another matrix from this one.
	 * Accidently supports multithreading... oh well
	 * @param rhs The matrix to subtract from this one, that satisfies: 
	 * rhs.rows() == this->rows() && rhs.cols() == this->cols()
	 * @return The result of subtraction matrix of the same dimensions).
	 * @throw bad_addition In case the matrix dimensions don't fit, a bad_addition
	 * exception is thrown.
	 * @throw bad_alloc this is thrown if memory for the result matrix could not be allocated
	 */
	const Matrix operator-(const Matrix& rhs) const
	{
		Matrix result(*this);
		_addOrSubtract(result, rhs, false); // false value --> subtraction
		return result;
	}

	/**
	 * Calculates the multiplication of this matrix by another.
	 * @param rhs A matrix that satisfies: rhs.rows() == this_matrix.cols()
	 * @return The result of the multiplication.
	 * @throw bad_multiplication if rhs.rows() != this_matrix.cols() a bad_multiplication
	 * exception will be thrown
	 * @throw bad_alloc if memory for the result matrix cannot be allocated.
	 * @throw
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
		{	// Perform parallel (by-line) multiplication
			_multithreadedMultiplication(result, rhs);
		}
		else
		{
			// Otherwise, perform sequential multiplication
			for (size_t i = 0; i < _rows; ++i)
			{	// Use the helper function to multiply
				_multiplyRow(result, *this, rhs, i);
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
		// If matrix dimensions don't fit they can't be identical.
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
	 * @throw matrix_index_out_of_range thrown if the given cordinates are out of the
	 * matrix's dimensions.
	 */
	T& operator()(size_t row, size_t col)
	{	// note that size_t can't be negative and 0 is OK value.
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
	 * @throw matrix_index_out_of_range thrown if the given cordinates are out of the
	 * matrix's dimensions.
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

	// ---------------------- member functions ----------------------
	
	/**
	 * @return The transpose of this matrix.
	 * @throw bad_alloc if memory for the result matrix can't be allocated
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
	 * @throw bad_trace if the matrix is not square, this is thrown.
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

	/**
	 * @return An iterator to the first cell of the matrix.
	 * if the matrix is empty, returns this->end()
	 */
	const_iterator begin()
	{
		return _data.begin();
	}
	
	/**
	 * @return An iterator to the end of the matrix.
	 */
	const_iterator end()
	{
		return _data.end();
	}

	/**
	 * @return true if the matrix is square, false otherwise.
	 */
	bool isSquareMatrix()
	{
		return _cols == _rows;
	}

	/**
	 * Sets the addition/subtraction/multiplication mode to be parallel/non-parallel
	 * to enable/disable multithreading on those operations respectively.
	 * @param isParallel true if you want multithreading, false otherwise
	 */
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
	// ------------------ Helper functions & methods ----------------

	/**
	 * Checks the matrices dimensions and performs addition / subtraction.
	 * @param result The result matrix
	 * @param rhs The matrix to add to 'dest'
	 * @param add Determines whether addition or subtraction will be performed
	 * @throw bad_addition In case the matrix dimensions don't fit, a bad_addition
	 * exception is thrown.
	 */
	void _addOrSubtract(Matrix& result, const Matrix& rhs, bool add = true) const
	{
		if (_rows != rhs._rows || _cols != rhs._cols)
		{
			throw bad_addition(MatDimensions(_rows, _cols), MatDimensions(rhs._rows, rhs._cols));
		}
		if (s_isParallel)
		{
			_multithreadAddition(result, rhs, add);
		}
		else
		{
			for (size_t row = 0; row < _rows; ++row)
			{	// Use the helper _addRow function to calculate the result
				_addRow(result, rhs, row, add);
			}
		}
	}

	/**
	 * Gets a result matrix, rhs and lhs and calculates the addition/subtracting of rhs and lhs.
	 * @param dest The result matrix
	 * @param rhs The right-hand-side matrix
	 * @param lhs The left-hand-size matrix
	 * @param add if true, dest = rhs + lhs.
	 *			otherwise, dest = rhs - lhs.
	 */
	static void _addRow(Matrix& dest, const Matrix& rhs, size_t row, bool add = true)
	{
		if (add)
		{
			for (size_t i = 0; i < dest._cols; ++i)
			{	// Direct access for efficiency.
				// Equivalent to: dest(row, i) += rhs(row, i);
				dest._data[row * dest._cols + i] += rhs._data[row * rhs._cols + i];
			}
		}
		else
		{ // Same for subtraction, duplicated to avoid checking 'add' on every iteration
			for (size_t i = 0; i < dest._cols; ++i)
			{
				dest._data[row * dest._cols + i] -= rhs._data[row * rhs._cols + i];
			}
		}		
	}

	/**
	 * Calculates the result of adding another matrix to this one.
	 * @param dest The result matrix (should be a copy of this one)
	 * @param rhs The matrix to add to dest
	 * @param add bool that determines whether addition or subtraction will be performed.
	 * @throw
	 */
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


	/**
	* This static function gets a result matrix reference, lhs and rhs matrices and a row number
	* and calculates the values of the result matrix's row.
	*/
	static void _multiplyRow(Matrix& dest, const Matrix& lhs, const Matrix& rhs, size_t i)
	{
		for (size_t j = 0; j < rhs._cols; ++j)
		{
			for (size_t k = 0; k < lhs._cols; ++k)
			{	// Direct access to avoid the boundry check of the operator().
				// This is equivalent to: dest(i, j) += lhs(i, k) * rhs(k, j);
				dest._data[i * dest._cols + j] += lhs._data[i * lhs._cols + k] *
												  rhs._data[k * rhs._cols + j];
			}
		}
	}

	/**
	* Calculates the result of multiplication of this matrix by another one.
	* @param dest the result matrix (dimensions: this.rows() x rhs.cols())
	* @param rhs the matrix to multiply
	* @throw
	*/
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
	
	// ----------------------- Data members -------------------------

	// s_isParallel - static bool to determine whether to use multithreading or not.
	static bool s_isParallel;
	size_t _rows, _cols;
	// MatData is just a vector of T objects that is the matrix's data
	MatData _data;
}; // ----------------- class definition ends here ------------------

// Multithreading is off by default.
template <typename T>
bool Matrix<T>::s_isParallel = false;

/**
 * A specialized transpoe method.
 * When called with a complex matrix, returns the hermitian transpose matrix of this one.
 * The result <A*> satisfies: for evey 0 <= i < rows, 0 <= j < cols: A*(i,j) = A(j,i).conj()
 * @return The conjugate transpose of this matrix.
 * @throw bad_alloc if memory for the result matrix cannot be allocated
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