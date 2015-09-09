#include "Matrix.hpp"


int main()
{
	Complex cmplx(1.5, 2.5);
	std::vector<Complex> vec(16, cmplx);
	Matrix<Complex> mat(2, 8, vec);
	mat(1, 6) = Complex(-3.2, 1);
	std::cout << "Result: " << std::endl;
	std::cout << mat << std::endl;
	std::cout << "Flattened: " << std::endl;
	auto it = mat.begin();
	for (; it != mat.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	std::cout << "Hermitian: " << std::endl;
	std::cout << mat.trans() << std::endl;
	return 0;
}