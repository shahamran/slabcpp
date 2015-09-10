#ifndef _MATRIX_EXCEPTIONS_HPP
#define _MATRIX_EXCEPTIONS_HPP

#include <stdexcept>
#include <sstream>
#include <iostream>

/**
 *
 */
struct MatDimensions
{
private:
	size_t _rows, _cols;

public:

	MatDimensions(size_t rows, size_t cols);

	MatDimensions();

	friend std::ostream& operator<<(std::ostream& os, const MatDimensions& dims);
};

/**
 *
 */
class bad_dimensions : public std::logic_error
{
protected:
	MatDimensions _dim1, _dim2;
	static std::ostringstream _oss;
	static std::string _msg;

public:

	bad_dimensions(MatDimensions dim1, MatDimensions dim2, 
				   const std::string& msg = "Matrix dimensions don't fit");

	bad_dimensions(MatDimensions dim, const std::string& msg = "Matrix dimensions don't fit");

	const char* what() const throw() override;
};

/**
 *
 */
class non_positive : public bad_dimensions
{
public:

	non_positive(const std::string& msg = "Bad matrix input");

	const char* what() const throw() override;
};

/**
 *
 */
class no_match : public bad_dimensions
{
public:

	no_match(MatDimensions mat_size, MatDimensions vec_size, 
			 const std::string& msg = "Invalid arguments");

	const char* what() const throw() override;
};

/**
 *
 */
class bad_addition : public bad_dimensions
{
public:

	bad_addition(MatDimensions first, MatDimensions second, 
				 const std::string& msg = "Addition/Subtraction could not be performed");
	
	const char* what() const throw() override;
};

/**
 *
 */
class bad_multiplication : public bad_dimensions
{
public:

	bad_multiplication(MatDimensions first, MatDimensions second,
					   const std::string& msg = "Multiplication could not be performed");

	const char* what() const throw() override;
};

/**
 *
 */
class bad_trace : public bad_dimensions
{
public:
	
	bad_trace(MatDimensions dims, 
			  const std::string& msg = "Cannot calculate trace on non-square matrix");

	const char* what() const throw() override;
};

/**
 *
 */
class matrix_index_out_of_range : public std::out_of_range
{
protected:
	static std::ostringstream _oss;
	MatDimensions _dims, _index;

public:

	matrix_index_out_of_range(MatDimensions dims, MatDimensions index);

	const char* what() const throw() override;
};

#endif
