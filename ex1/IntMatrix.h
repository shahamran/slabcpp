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

	/**
	 * The assignment operator. This IntMatrix will have the same values as the copied one.
	 * 
	 * @param other The IntMatrix to copy.
	 */
	IntMatrix& operator=(IntMatrix other);

	/**
	 * Calculates the addition of another matrix to this one.
	 * Only call with a matrix that has the same dimensions as this one.
	 * 
	 * @param other A matrix with the same dimensions as this one to add.
	 * @return An IntMatrix which is the result of the addition.
	 */
	IntMatrix operator+(const IntMatrix& other) const;

	/**
	 * Adds a matrix to this one.
	 * Only call with another matrix with the same dimensions.
	 * 
	 * @param other Another IntMatrix with the same dimensions.
	 */
	IntMatrix& operator+=(const IntMatrix& other);

	/**
	 * Calculates the product of multiplication of this matrix by another one.
	 * Only call with a matrix that satisfy (this->_cols == other._rows).
	 * 
	 * @param other Another matrix with the right dimensions (see above).
	 * @return The matrix multiplication result.
	 */
	IntMatrix operator*(const IntMatrix& other) const;

	/**
	 * Calculates the multiplication of this matrix by a scalar (integer).
	 * 
	 * @param scalar The scalar by which the matrix will be multiplied
	 * @return The result of the multiplication by scalar.
	 */
	IntMatrix operator*(int scalar) const;

	/**
	 * Multiplies this matrix by another.
	 * 
	 * @param other The matrix by which this matrix will be multiplied
	 */
	IntMatrix& operator*=(const IntMatrix& other);

	/**
	 * Calculates the subtraction of another matrix from this one.
	 * Only call with a matrix that has the same dimensions as this one.
	 * 
	 * @param other A matrix with the same dimensions as this one to subtact.
	 * @return An IntMatrix which is the result of the subtraction.
	 */
	IntMatrix operator-(const IntMatrix& other) const;

	/**
	 * Subtracts a matrix from this one.
	 * Only call with another matrix with the same dimensions.
	 * 
	 * @param other Another IntMatrix with the same dimensions.
	 */
	IntMatrix& operator-=(const IntMatrix& other);

	/**
	 * 'Prints' this matrix to a given out-stream.
	 * Writing is done in the following format:
	 * Each matrix entry is followed by a space character except the last one in the line.
	 * Every two lines are separated by a single newline ('\n') char.
	 * 
	 * @param out An output stream object
	 * @param mat The IntMatrix object reference.
	 */
	friend ostream& operator<<(ostream& out, const IntMatrix& mat);

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
	friend istream& operator>>(istream& in, IntMatrix& mat);

	/**
	 * @return The transpose of this matrix.
	 */
	IntMatrix trans() const;

	/**
	 * Make sure this matrix is square before using this function.
	 * The check can be done by the isSquare() function.
	 * 
	 * @return The trace of this matrix.
	 */
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

	/**
	 * @return Returns the number of rows of this matrix.
	 */
	size_t getRows() const
	{
		return (_rows);
	}

	/**
	 * @return The number of columnts of this matrix.
	 */
	size_t getCols() const
	{
		return (_cols);
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
