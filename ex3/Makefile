CC = g++

C_FLAGS = -std=c++11 -Wall -Wextra -Wvla -pthread
TEST_NAME = test
PARALLEL = ParallelChecker
PARALLEL_FILES = ParallelChecker.cpp Complex.cpp MatrixExceptions.cpp
TAR_NAME = ex3.tar
TAR_FILES = Matrix.hpp MatrixExceptions.hpp MatrixExceptions.cpp README
VALGRIND_FLAGS = --leak-check=full --show-possibly-lost=yes --show-reachable=yes \
			     --undef-value-errors=yes

# Creates Matrix.hpp.gch object file
Matrix: Matrix.hpp MatrixExceptions.hpp
	${CC} ${C_FLAGS} -c $<

# Create the optimized parallel check file
${PARALLEL}: ${PARALLEL_FILES} Complex.h Matrix.hpp MatrixExceptions.hpp
	${CC} ${C_FLAGS} -O -DNDEBUG ${PARALLEL_FILES} -o $@

# The generic matrix driver toolset
${TEST_NAME}: Complex.o GenericMatrixDriver.o MatrixExceptions.o
	${CC} ${C_FLAGS} $^ -o $@

# Valgrind test
ValgrindMe: ${TEST_NAME}	
	valgrind ${VALGRIND_FLAGS} ./${TEST_NAME}

# The rule for creating .o files
%.o: %.cpp
	${CC} ${C_FLAGS} -c $<

# The submission tar file creator
tar: ${TAR_FILES}
	tar -cvf ${TAR_NAME} ${TAR_FILES}

# Cleans up the mess (object files, executables and tests)
clean:
	rm -fv *.o *.gch *.exe* ${TEST_NAME} ${PARALLEL}

.PHONY: clean all tar Matrix