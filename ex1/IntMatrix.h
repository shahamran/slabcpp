#ifndef INT_MATRIX_H
#define INT_MATRIX_H

/********************************************************************************
 * @file IntMatrix.h
 * @author  ransha <ran.shaham1@mail.huji.ac.il>
 * @version 1.0
 * @date 25 Aug 2015
 * 
 * @brief Ran Shaham's IntMatrix class.
 *
 * @section LICENSE
 * This program is not a free software; 
 *
 * @section DESCRIPTION
 * Ran Shaham's IntMatrix class.
 *
 * This file provides an interface to a basic IntMatrix object which includes
 * simple operations on matrices of integers, such as addition, substraction,
 * multiplication etc.
 ********************************************************************************/

using namespace std;

#include <iostream> // For istream and ostream
#include <sstream> // 
// The separator for matrix input
#define INPUT_SEPARATOR ','

/**
 * An IntMatrix class.
 * This class represents a matrix of integers.
 */
class IntMatrix
{
public:
	/**
	 * The most basic constructor for an IntMatrix object.
	 * Allocates a dynamic 2d array of ints (int** _data).
	 * 
	 * @param rows The number of rows in this matrix
	 * @param cols The number of columns in this matrix
	 */
	IntMatrix(size_t rows, size_t cols);

	/**
	 * A shallow-copy constructor that steals the allocated data from the given
	 * rvalue IntMatrix.
	 * 
	 * @param rvalue An rvalue IntMatrix object.
	 */
	IntMatrix(IntMatrix&& rvalue);

	/**
	 * A deep-copy constructor that creates a new independent data array which is a copy of
	 * the given IntMatrix.
	 * 
	 * @param toCopy The IntMatrix object to copy.
	 */
	IntMatrix(const IntMatrix &toCopy);

	/**
	 * Default constructor for IntMatrix. Constructs an IntMatrix with 0 rows
	 * and 0 columnts (meaning no memory is allocated for _data).
	 */
	IntMatrix();

	/**
	 * Destructor for IntMatrix object. Deletes all data allocated to this matrix.
	 */
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

	IntMatrix trans() const;

	int trace() const;

	/**
	 * Checks if the IntMatrix <other> can be added to this IntMatrix object
	 * (dimensions-wise).
	 * 
	 * @param other The other IntMatrix.
	 * @return True if the dimensions fit, false otherwise.
	 */
	bool canBeAddedBy(const IntMatrix& other) const
	{
		return (_cols == other._cols && _rows == other._rows);
	}

	/**
	 * Checks if this IntMatrix can be multiplied by <other> IntMatrix (dimensions-wise).
	 * 
	 * @param other The IntMatrix to multiply
	 * @return True if the dimensions fit, false otherwise.
	 */
	bool canBeMultipliedBy(const IntMatrix& other) const
	{
		return (_cols == other._rows);
	}

	/**
	 * @return True if this matrix is square, false otherwise.
	 */
	bool isSquare() const
	{
		return (_rows == _cols);
	}
private:
	/**
	 * A swap function that replaces this matrix's internal members with the other matrix.
	 * 
	 * @param toSwap The matrix to be swapped with.
	 */
	void swap(IntMatrix& toSwap);
	size_t _rows, _cols;
	// The dynamic 2d array that keeps the data for this matrix.
	int** _data;
};


#endif
