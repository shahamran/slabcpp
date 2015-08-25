#include "IntMatrix.h"
#define MAT_SEP "--------"
#define RESULT_SEP "=========="
#define NUM_OF_OPS 5
#define EMPTY_STRING ""

enum OpId
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

typedef struct MatrixOperation
{
	OpId _id;
	string _name;
	Result _result;
	string (*_opHandler)(MatrixOperation& op);
} MatrixOperation;

void printResult(Result resultType, void* result, string msg = "Matrix is square and its trace is: ")
{
	switch (resultType)
	{
	case MATRIX:
		cout << RESULT_SEP << endl << "Resulted matrix:\n" << endl << *(IntMatrix*)result << endl;
		break;
	case NUMBER:
		cout << msg << *(int*)result << endl;
		break;
	}
}

IntMatrix getMatrix()
{
	size_t rows, cols;
	cout << "number of rows:";
	cin >> rows;
	cout << "number of columns:";
	cin >> cols;
	cout << "Now insert the values of the matrix, row by row.\n"
		 << "After each cell add the char '" << INPUT_SEPARATOR << "' "
         <<  "(including after the last cell of a row).\n"
		 <<  "Each row should be in a separate line." << endl;
	IntMatrix result = IntMatrix(rows, cols);
	cin >> result;
	return result;
}

void printMatrix(const string name, const IntMatrix& mat)
{
	cout << MAT_SEP << endl;
	cout << "Got " << name << "matrix:" << endl;
	cout << endl << mat << endl;
}

string twoOperandsOperation(MatrixOperation& op)
{
	cout << "Operation " << op._name << " requires 2 operand matrices." << endl;
	string firstName = "first ", secondName = "second ";
	cout << "Insert " << firstName << "matrix:" << endl;
	IntMatrix firstMat = getMatrix();
	cout << "Insert " << secondName << "matrix:" << endl;
	IntMatrix secondMat = getMatrix();
	printMatrix(firstName, firstMat);
	printMatrix(secondName, secondMat);
	IntMatrix result;
	switch (op._id)
	{
	case ADD:
		if (firstMat.canBeAddedBy(secondMat))
		{
			result = firstMat + secondMat;
			break;
		}
		else
		{
			return "different dimensions";
		}
	case SUB:
		if (firstMat.canBeAddedBy(secondMat))
		{
			result = firstMat - secondMat;
			break;
		}
		else
		{
			return "different dimensions";
		}
	case MUL:
		if (firstMat.canBeMultipliedBy(secondMat))
		{
			result = firstMat * secondMat;
			break;
		}
		else
		{
			return "different dimensions";
		}
	default:
		break;
	}
	printResult(MATRIX, &result);
	return EMPTY_STRING;
}

string oneOperandOperation(MatrixOperation& op)
{
	cout << "Operation " << op._name << " requires 1 operand matrix." << endl;
	IntMatrix result;

	switch (op._id)
	{
	case TRANS:
		printMatrix(EMPTY_STRING, result = getMatrix());
		printResult(MATRIX, (void*) &result.trans());
		break;
	case TRACE:
		printMatrix(EMPTY_STRING, result = getMatrix());
		if (result.isSquare())
		{
			int trace = result.trace();
			printResult(NUMBER, (void*)&trace);
			break;
		}
		else
		{
			return "The matrix isn't square";
		}
	default:
		break;
	}
	return EMPTY_STRING;
}

MatrixOperation getOp()
{
	MatrixOperation add = { ADD, "add", MATRIX, twoOperandsOperation },
					sub = { SUB, "sub", MATRIX, twoOperandsOperation },
					mul = { MUL, "mul", MATRIX, twoOperandsOperation },
					transpose = { TRANS, "trans", MATRIX, oneOperandOperation },
					trace = { TRACE, "trace", NUMBER, oneOperandOperation },
					selectedOp;
	MatrixOperation ops[] = { add, sub, mul, transpose, trace };
	int selectedId;
	do
	{
		cout << "Choose operation:" << endl;
		for (int i = 0; i < NUM_OF_OPS; i++)
		{
			cout << ops[i]._id << ". " << ops[i]._name << endl;
		}
		cin >> selectedId;
	}
	while (selectedId < ADD || selectedId > TRACE);
	return ops[selectedId - 1];
}

int main()
{
	MatrixOperation selectedOp = getOp();
	string errorStr = selectedOp._opHandler(selectedOp);
	if (errorStr != EMPTY_STRING)
	{
		cout << "Error: " << selectedOp._name << " failed - " << errorStr << "." << endl;
		return 1;
	}
	return 0;
}