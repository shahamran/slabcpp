#include "IntMatrix.h"
#define SEPARATOR ','
#define MAT_SEP "--------"
#define RESULT_SEP "=========="

enum MatrixOp
{
	ADD = 1,
	SUB = 2,
	MUL = 3,
	TRANS = 4,
	TRACE = 5
};

enum Result
{ 
	MATRIX = 0,
	NUMBER = 1 
};

typedef struct
{
	MatrixOp _id;
	string _name;
	Result _result;
	void (*opHandler)(MatrixOperation);
} MatrixOperation;

IntMatrix& getMatrix()
{
	size_t rows, cols;
	cout << "number of rows:";
	cin >> rows;
	cout << "number of columns:";
	cin >> cols;
	cout << "Now insert the values of the matrix, row by row\n \
		     After each cell add the char '" << SEPARATOR << "'\
             (including after the last cell of a row).\n \
			 Each row should be in a separate line." << endl;
	IntMatrix* result = new IntMatrix(rows, cols);
	return *result;
}

void printMatrix(const string name, const IntMatrix& mat)
{
	cout << MAT_SEP << endl;
	cout << "Got " << name << "matrix:" << endl;
	cout << endl << mat << endl;
}

void twoOperandsOperation(MatrixOperation& op)
{
	cout << "Operation " << op._name << " requires 2 operand matrices." << endl;
	cout << "Insert first matrix:" << endl;
	IntMatrix firstMat = getMatrix();
	cout << "Insert second matrix:" << endl;
	IntMatrix secondMat = getMatrix();
	printMatrix("first ", firstMat);
	printMatrix("second ", secondMat);
	IntMatrix result;
	switch (op._id)
	{
	case ADD:
		result = firstMat + secondMat;
		break;
	case SUB:
		result = firstMat - secondMat;
		break;
	case MUL:
		if (firstMat.getCols() == secondMat.getRows())
		{
			result = firstMat * secondMat;
			break;
		}
		else
		{

		}
		
	}
	printResult(MATRIX, &result);
}

void oneOperandOperation(MatrixOperation& op)
{
	cout << "Operation " << op._name << " requires 1 operand matrix." << endl;
	IntMatrix result;
	switch (op._id)
	{
	case TRANS:
		result = getMatrix().trans();
		printResult(MATRIX, (void*) &result);
		break;
	case TRACE:
		result = getMatrix();
		if (result.isSquare())
		{
			int trace = result.trace();
			printResult(NUMBER, (void*)&trace);
			break;
		}
		else
		{

		}
		break;
	}
}

void printResult(Result resultType, void* result)
{
	switch (resultType)
	{
	case MATRIX:
		cout << RESULT_SEP << endl << "Resulted Matrix:\n" << endl << *(IntMatrix*)result << endl;
		break;
	case NUMBER:
		cout << 
	}
}

int main()
{
	MatrixOperation add = { ADD, "add", MATRIX, twoOperandsOperation },
					mul = { MUL, "mul", MATRIX, twoOperandsOperation },
					sub = { SUB, "sub", MATRIX, twoOperandsOperation },
					transpose = { TRANS, "trans", MATRIX,  oneOperandOperation },
					trace = { TRACE, "trace", NUMBER, oneOperandOperation };
	MatrixOperation ops[] = { add, sub, mul, transpose, trace };
	int selectedOp;
	cout << "Choose operation:" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << ops[i]._id << ". " << ops[i]._name << endl;
	}
	cin >> selectedOp;
	selectedOp--;
	ops[selectedOp].opHandler(ops[selectedOp]);
}