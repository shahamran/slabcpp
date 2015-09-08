#ifndef _MATRIX_HPP
#define _MATRIX_HPP

#include <iostream>
#include <vector>
#include <thread>
#include "Complex.h"

#define DEFAULT_VALUE 0
#define DEFAULT_SIZE 1

template <typename T>
class Matrix
{
public:

	typedef T value_type;
	typedef std::vector<T> MatRow; // A row in the matrix

	friend void swap(Matrix<T>& mat, Matrix<T>& other)
	{
		std::swap(mat._rows, other._rows);
		std::swap(mat._cols, other._cols);
		std::swap(mat._data, other._data);
		return;
	}

	/**
	 * Constructor for a matrix. Creates a 1x1 matrix with the value 0, by default.
	 */
	Matrix(size_t rows = DEFAULT_SIZE, size_t cols = DEFAULT_SIZE) :
		_rows(rows), _cols(cols)
	{
		_data = std::vector<MatRow>(rows);
		for (size_t i = 0; i < rows; i++)
		{
			_data[i] = MatRow(cols, DEFAULT_VALUE);
		}
	}

	/**
	 * Copy constructor.
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
	 * Move constructor.
	 */
	Matrix(Matrix<T> && rvalue) :
		Matrix<T>()
	{
		swap(*this, rvalue);
		return *this;
	}

	/**
	 * Creates a matrix with the given dimensions and the values set by the given vector.
	 * ( Assumes cells.size() == rows * cols ).
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


	Matrix<T>& operator=(Matrix<T> rhs)
	{
		swap(*this, rhs);
		return *this;
	}


	const Matrix<T> operator+(const Matrix<T>& rhs) const
	{
		if (_rows != rhs._rows || _cols != rhs._cols)
		{
			// Throw dimension exception
		}
		// Parellel / non-Parellel
	}


	const Matrix<T> operator-(const Matrix<T>& rhs) const
	{
		// Same
	}


	const Matrix<T> operator*(const Matrix<T>& rhs) const
	{
		if (_cols != rhs._rows)
		{
			// Throw exception
		}
		// Same
	}


	bool operator==(const Matrix<T>& rhs) const
	{
		if (_rows != rhs._rows || _cols != rhs._cols)
		{
			return false;
		}
		// Use iterator to check equiality
	}
	
	
	bool operator!=(const Matrix<T>& rhs) const
	{
		return !operator==(rhs);
	}
	

	T& operator()(size_t row, size_t col)
	{
		return _data[row][col];
	}
	

	const T& operator()(size_t row, size_t col) const
	{
		return (const)_data[row][col];
	}	
	
	
	Matrix<T> trans() const
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
	
	
	friend std::ostream& operator<<(ostream& os, const Matrix<T>& mat);
	
	
	size_t rows() const
	{
		return _rows;
	}


	size_t cols() const
	{
		return _cols;
	}

private:
	
	int _rows, _cols;
	std::vector<MatRow> _data;
};

template<>
Matrix<Complex> Matrix<Complex>::trans() const
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