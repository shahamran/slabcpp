#ifndef INT_MATRIX_H
#define INT_MATRIX_H

class IntMatrix
{
public:
	IntMatrix();
	IntMatrix(const IntMatrix &toCopy);
	IntMatrix& operator=(const IntMatrix& other);
	IntMatrix& operator+(const IntMatrix& other);
	IntMatrix& operator+=(const IntMatrix& other);
	IntMatrix& operator*(const IntMatrix& other);
	IntMatrix& operator*=(const IntMatrix& other);
	// IntMatrix& operator<<...
	IntMatrix& trans(const IntMatrix& toTrans) const;
	int trace() const;
	~IntMatrix();
private:

};


#endif
