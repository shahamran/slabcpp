#include "IntMatrix.h"

#define MAT_SEP "--------"
#define RESULT_SEP "=========="
#define NUM_OF_OPS 5
#define EMPTY_STRING ""
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

/**
 * Enum for the operations numbers
 */
enum OpId
{
	ADD = 1,
	SUB = 2,
	MUL = 3,
	TRANS = 4,
	TRACE = 5
};

/**
 * Enum for the result type (in case we add more operations)
 */
enum Result
{ 
	MATRIX = 0,
	NUMBER = 1 
};

/**
 * A struct that represents a matrix operation.
 * Holds a name, the result type and a function.
 */
typedef struct MatrixOperation
{
	OpId _id;
	string _name;
	Result _result;
	string (*_opHandler)(MatrixOperation& op);
} MatrixOperation;

/**
 * Prints the given result. Can accept a number or a matrix pointer.
 * 
 * @param  resultType The result type.
 * @param result A pointer to the result (IntMatrix* or int*)
 * @param msg In case the result is a number, specify what message will be displayed.
 * 			  Default is trace message.
 */
void printResult(Result resultType, void* result, 
				 string msg = "The matrix is square and its trace is ")
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

/**
 * Asks the user for matrix input.
 * @return The IntMatrix object as specified in the user input.
 */
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
	IntMatrix inputMat = IntMatrix(rows, cols);
	cin >> inputMat;
	return inputMat;
}

/**
 * Prints the given matrix.
 * @param mat The matrix to print.
 * @param name The name of the matrix. Default name is "" (no name).
 */
void printMatrix(const IntMatrix& mat, const string name = EMPTY_STRING)
{
	string msg = name == EMPTY_STRING ? "got matrix:" : "Got " + name + "matrix:";
	cout << MAT_SEP << endl;
	cout << msg << endl;
	cout << endl << mat << endl;
}

/**
 * Gets two matrices from the user and runs the given operation, only if the operation
 * can be performed. Then prints the result. 
 * If the operation could be done, returns an error (string) message.
 * 
 * @param op The matrix operation
 * @return An error message if the operation could not be performed, "" (empty string) otherwise.
 */
string twoOperandsOperation(MatrixOperation& op)
{
	cout << "Operation " << op._name << " requires 2 operand matrices." << endl;
	// Gets two matrices.
	string firstName = "first ", secondName = "second ";
	cout << "Insert " << firstName << "matrix:" << endl;
	IntMatrix firstMat = getMatrix();
	cout << "Insert " << secondName << "matrix:" << endl;
	IntMatrix secondMat = getMatrix();
	// Print matrices.
	printMatrix(firstMat, firstName);
	printMatrix(secondMat, secondName);
	// Perform operation
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
	// Print result
	printResult(MATRIX, &result);
	return EMPTY_STRING;
}

/**
 * Gets a matrix from the user and performs the given operation. Then prints the result.
 * @param op The matrix operation
 * @return An error string message if the operation couldn't be done, EMPTY_STRING if the
 * operation was performed.
 */
string oneOperandOperation(MatrixOperation& op)
{
	cout << "Operation " << op._name << " requires 1 operand matrix." << endl;
	IntMatrix result;

	switch (op._id)
	{
		case TRANS:
			printMatrix(result = getMatrix());
			result = result.trans();
			printResult(MATRIX, (void*) &result);
			break;
		case TRACE:
			printMatrix(result = getMatrix());
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

/**
 * Gets the desired operation from the user.
 */
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

/**
 * The main function that runs when program is being run
 */
int main()
{
	MatrixOperation selectedOp = getOp();
	string errorStr = selectedOp._opHandler(selectedOp);
	if (errorStr != EMPTY_STRING)
	{  // If operation failed, print the error message.
		cout << "Error: " << selectedOp._name << " failed - " << errorStr << "." << endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}