#include "MatrixExceptions.hpp"

#define UNDEFINED 0
#define LEFT_BOUND '<'
#define RIGHT_BOUND '>'

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
	os << LEFT_BOUND << dims._rows << "x" << dims._cols << RIGHT_BOUND;
	return os;
}

// bad_dimensions exception

std::ostringstream bad_dimensions::_oss("");
std::string bad_dimensions::_msg("");

bad_dimensions::bad_dimensions(MatDimensions dim1, MatDimensions dim2, const std::string& msg) :
	logic_error(msg.c_str()), _dim1(dim1), _dim2(dim2)
{
}

bad_dimensions::bad_dimensions(MatDimensions dim, const std::string& msg) :
	bad_dimensions(dim, MatDimensions(), msg)
{
}

const char* bad_dimensions::what() const throw()
{
	_oss.str("");
	_oss << logic_error::what() << ": " <<  _msg;
	return _oss.str().c_str();
}

// non_positive

non_positive::non_positive(const std::string& msg) :
	bad_dimensions(MatDimensions(), msg)
{
}

const char* non_positive::what() const throw()
{
	_msg = "Cannot construct a matrix with non-positive dimensions";
	return bad_dimensions::what();
}

// no_match exception

no_match::no_match(MatDimensions mat_size, MatDimensions vec_size, const std::string& msg) :
	bad_dimensions(mat_size, vec_size, msg)
{
}

const char* no_match::what() const throw()
{
	_oss.str("");
	_oss << "Cannot fit a " << _dim2 << " sized vector"
		 << " to a " << _dim1 << " matrix";
	_msg = _oss.str();
	return bad_dimensions::what();
}

// bad_addition exception

bad_addition::bad_addition(MatDimensions first, MatDimensions second, const std::string& msg) :
	bad_dimensions(first, second, msg)
{
}

const char* bad_addition::what() const throw()
{
	_oss.str("");
	_oss << "A " << _dim2 << " matrix"
				 << " cannot be added to a " << _dim1 << " matrix";
	_msg = _oss.str();
	return bad_dimensions::what();
}

// bad_multiplication exception

bad_multiplication::bad_multiplication(MatDimensions first, MatDimensions second, 
									   const std::string& msg) :
	bad_dimensions(first, second, msg)
{
}

const char* bad_multiplication::what() const throw()
{
	_oss.str("");
	_oss << "A " << _dim1 << " matrix"
		 << " cannot be multiplied by a " << _dim2 << " matrix";
	_msg = _oss.str();
	return bad_dimensions::what();
}

// bad_trace exception

bad_trace::bad_trace(MatDimensions dims, const std::string& msg) :
	bad_dimensions(dims, msg)
{
}

const char* bad_trace::what() const throw()
{
	_oss.str("");
	_oss << "Got " << _dim1 << " matrix";
	_msg = _oss.str();
	return bad_dimensions::what();
}

// out_of_matrix_range

std::ostringstream matrix_index_out_of_range::_oss("");

matrix_index_out_of_range::matrix_index_out_of_range(MatDimensions dims, MatDimensions index) :
	out_of_range("Index out of range"), _dims(dims), _index(index)
{
}

const char* matrix_index_out_of_range::what() const throw()
{
	_oss.str("");
	_oss << out_of_range::what() << ": there is no index " << _index
		 << " in a " << _dims << " matrix";
	return _oss.str().c_str();
}