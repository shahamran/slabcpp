// This file includes all exceptions that are thrown by the generic matrix class

#ifndef _MATRIX_EXCEPTIONS_HPP
#define _MATRIX_EXCEPTIONS_HPP

#include <stdexcept>
#include <sstream>
#include <iostream>

#define UNDEFINED 0
#define LEFT_BOUND '<'
#define RIGHT_BOUND '>'
// -----------------------------------------------------------------------------------------------
/**
 * This struct holds a pair of size_t that represent matrix dimensions.
 */
struct MatDimensions
{
private:
	size_t _rows, _cols;

public:
	/**
	 * Constructs a matrix dimensions object from the given values
	 */
	MatDimensions(size_t rows, size_t cols) :
		_rows(rows), _cols(cols)
	{
	}
	/**
	 * Default is 0x0
	 */
	MatDimensions() :
		_rows(UNDEFINED), _cols(UNDEFINED)
	{
	}
	/**
	 * Prints the dimensions ins the format <RxC> where R stands for ROW and C for COLUMN
	 */
	friend std::ostream& operator<<(std::ostream& os, const MatDimensions& dims)
	{
		os << LEFT_BOUND << dims._rows << "x" << dims._cols << RIGHT_BOUND;
		return os;
	}
};
// -----------------------------------------------------------------------------------------------
/**
 * A logic_error exception that is thrown when an operation on matrices cannot be performed
 * because of wrong dimensions.
 */
class bad_dimensions : public std::logic_error
{
protected:
	MatDimensions _dim1, _dim2;
	static std::ostringstream _oss;
	static std::string _msg;

public:
	/**
	 * Constructor for binary operation dimensions error, gets the dimensions of the two
	 * matrices and can take also a message string
	 */
	bad_dimensions(MatDimensions dim1, MatDimensions dim2, 
				   const std::string& msg = "Matrix dimensions don't fit") :
		logic_error(msg.c_str()), _dim1(dim1), _dim2(dim2)
	{
	}
	/**
	 * Constructor for unary operation dimensions error, gets the dimensions of the matrix
	 * and can also take an informative message.
	 */
	bad_dimensions(MatDimensions dim, const std::string& msg = "Matrix dimensions don't fit") :
		bad_dimensions(dim, MatDimensions(), msg)
	{
	}
	/**
	 * Renders the message more informative through the given message
	 * (extending classes can change _msg value to influence this)
	 */
	const char* what() const throw() override
	{
		_oss.str("");
		_oss << logic_error::what() << ": " << _msg;
		return _oss.str().c_str();
	}
};
// Initialize the stringstream and the message to be blank
std::ostringstream bad_dimensions::_oss("");
std::string bad_dimensions::_msg("");
// -----------------------------------------------------------------------------------------------
/**
 * This is thrown when trying to create a matrix with exactly one dimensions 0
 */
class non_positive : public bad_dimensions
{
public:
	/**
	 * Constructs an exception with default message
	 */
	non_positive(const std::string& msg = "Bad matrix input") :
		bad_dimensions(MatDimensions(), msg)
	{
	}
	/**
	 * explains what is wrong
	 */
	const char* what() const throw() override
	{
		_msg = "Cannot construct a matrix with non-positive dimensions";
		return bad_dimensions::what();
	}
};
// -----------------------------------------------------------------------------------------------
/**
 * This exception is thrown when trying to fit a vector of elements to a matrix and the
 * size of the vector does not match the matrix size.
 */
class no_match : public bad_dimensions
{
public:
	/**
	 * Constructs an exception with default message.
	 */
	no_match(MatDimensions mat_size, MatDimensions vec_size, 
			 const std::string& msg = "Invalid arguments") :
		bad_dimensions(mat_size, vec_size, msg)
	{
	}
	/**
	 * Explains in details what is wrong.
	 */
	const char* what() const throw() override
	{
		_oss.str("");
		_oss << "Cannot fit a " << _dim2 << " sized vector"
			<< " to a " << _dim1 << " matrix";
		_msg = _oss.str();
		return bad_dimensions::what();
	}
};
// -----------------------------------------------------------------------------------------------
/**
 * This is thrown when trying to add two matrices whose dimensions don't fit.
 */
class bad_addition : public bad_dimensions
{
public:
	/**
	 * Constructs the exception with the matrices dimensions
	 */
	bad_addition(MatDimensions first, MatDimensions second, 
				 const std::string& msg = "Addition/Subtraction could not be performed") :
		bad_dimensions(first, second, msg)
	{
	}
	/**
	 * Detailed explanation
	 */
	const char* what() const throw() override
	{
		_oss.str("");
		_oss << "A " << _dim2 << " matrix"
			<< " cannot be added to a " << _dim1 << " matrix";
		_msg = _oss.str();
		return bad_dimensions::what();
	}
};
// -----------------------------------------------------------------------------------------------
/**
 * This is thrown when trying to multiply matrices with wrong dimensions
 */
class bad_multiplication : public bad_dimensions
{
public:
	/**
	* Constructs the exception with the matrices dimensions
	*/
	bad_multiplication(MatDimensions first, MatDimensions second,
					   const std::string& msg = "Multiplication could not be performed") :
		bad_dimensions(first, second, msg)
	{
	}
	/**
	* Detailed explanation
	*/
	const char* what() const throw() override
	{
		_oss.str("");
		_oss << "A " << _dim1 << " matrix"
			<< " cannot be multiplied by a " << _dim2 << " matrix";
		_msg = _oss.str();
		return bad_dimensions::what();
	}
};
// -----------------------------------------------------------------------------------------------
/**
 * This is thrown when trying to calculate trace on non-square matrix
 */
class bad_trace : public bad_dimensions
{
public:
	/**
	 * Constructs an exception with the matrix dimensions.
	 */
	bad_trace(MatDimensions dims, 
			  const std::string& msg = "Cannot calculate trace on non-square matrix") :
		bad_dimensions(dims, msg)
	{
	}
	/**
	 * Shows the bad matrix dimensions.
	 */
	const char* what() const throw() override
	{
		_oss.str("");
		_oss << "Got " << _dim1 << " matrix";
		_msg = _oss.str();
		return bad_dimensions::what();
	}
};
// -----------------------------------------------------------------------------------------------
/**
 * This is thrown when trying to access a cell in the matrix that does not exist.
 */
class matrix_index_out_of_range : public std::out_of_range
{
protected:
	static std::ostringstream _oss;
	MatDimensions _dims, _index;

public:
	/**
	 * Takes the matrix dimensions and the index that was entered in the form of
	 * matrix dimensions. e.g. let mat be a 2x2 matrix, when trying to access
	 * mat(2,0) this exception will take the arguments 2x2 (for matrix dims) and 2x0 (for index).
	 */
	matrix_index_out_of_range(MatDimensions dims, MatDimensions index) :
		out_of_range("Index out of range"), _dims(dims), _index(index)
	{
	}
	/**
	 * Detailed explanation
	 */
	const char* what() const throw() override
	{
		_oss.str("");
		_oss << out_of_range::what() << ": there is no index " << _index
			<< " in a " << _dims << " matrix";
		return _oss.str().c_str();
	}
};
// Initialized the stringstream with empty string
std::ostringstream matrix_index_out_of_range::_oss("");
// -----------------------------------------------------------------------------------------------
#endif
