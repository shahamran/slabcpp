#include "MatrixExceptions.hpp"
#define UNDEFINED 0

// MatDimensions struct

MatDimensions::MatDimensions() :
	_rows(UNDEFINED), _cols(UNDEFINED)
{
}

MatDimensions::MatDimensions(size_t rows, size_t cols) :
	_rows(rows), _cols(cols)
{
}

std::ostream& operator<<(std::ostream& os, const MatDimensions& dims)
{
	if (dims._rows && dims._cols)
	{
		os << dims._rows << "x" << dims._cols;
	}
	else
	{
		os << "<empty>";
	}
	return os;
}

// bad_dimensions exception
bad_dimensions::bad_dimensions(MatDimensions dim1, MatDimensions dim2, const std::string& msg) :
	logic_error(msg), _dim1(dim1), _dim2(dim2)
{
}

bad_dimensions::bad_dimensions(MatDimensions dim, const std::string& msg) :
	logic_error(msg), _dim1(dim), _dim2()
{
}

std::ostringstream bad_dimensions::_oss("");

// non_positive

const char* non_positive::what() const throw()
{
	_oss.str("");
	_oss << bad_dimensions::what() << ": Cannot construct a matrix with non-positive dimensions";
	return _oss.str().c_str();
}

// bad_addition exception
bad_addition::bad_addition(MatDimensions first, MatDimensions second) :
	bad_dimensions(first, second, "Addition/Subtraction could not be performed")
{
}

const char* bad_addition::what() const throw()
{
	_oss.str("");
	_oss << bad_dimensions::what() << ": A " << _dim2 << " matrix"
				 << " cannot be added to a " << _dim1 << " matrix";
	return _oss.str().c_str();
}

// bad_multiplication exception

const char* bad_multiplication::what() const throw()
{
	_oss.str("");
	_oss << bad_dimensions::what() << ": A " << _dim1 << " matrix"
			<< " cannot be multiplied by a " << _dim2 << " matrix";
	return _oss.str().c_str();
}

// bad_trace exception

const char* bad_trace::what() const throw()
{
	_oss.str("");
	_oss << bad_dimensions::what() << ": cannot calculate trace on a " << _dim1 << " matrix";
	return _oss.str().c_str();
}