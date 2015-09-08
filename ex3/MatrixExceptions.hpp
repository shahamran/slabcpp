#ifndef _MATRIX_EXCEPTIONS_HPP
#define _MATRIX_EXCEPTIONS_HPP

#include <stdexcept>

class bad_dimensions : public std::logic_error
{
public:
	bad_dimensions() : logic_error("Matrix dimensions don't fit")
	{
	}

	bad_dimensions(const std::string& msg) : logic_error(msg)
	{
	}
};

class bad_addition : public bad_dimensions
{
public:
	bad_addition(size_t rows1, size_t rows2, size_t cols1, size_t cols2) : 
		bad_dimensions("Couldn't add matrices")
	{

	}
};

#endif
