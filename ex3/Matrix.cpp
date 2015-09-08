#include "Matrix.hpp"


int main()
{
	Matrix<int> mat(2, 2);
	mat(0, 0) = 1;
	mat(0, 1) = 2;
	mat(1, 0) = 3;
	mat(1, 1) = 4;
	std::cout << "Result: " << std::endl;
	std::cout << mat << std::endl;
	return 0;
}