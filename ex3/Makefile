CC = g++

C_FLAGS = -std=c++11 -Wall -Wextra
TEST_NAME = test
TAR_NAME = ex3.tar
TAR_FILES = Matrix.hpp MatrixExceptions.hpp
VALGRIND_FLAGS = --leak-check=full --show-possibly-lost=yes --show-reachable=yes --undef-value-errors=yes

${TEST_NAME}: Complex.o GenericMatrixDriver.o MatrixExceptions.o
	${CC} ${C_FLAGS} $^ -o $@

%.o: %.cpp
	${CC} ${C_FLAGS} -c $<

tar: ${TAR_FILES}
	tar -cvf ${TAR_NAME} ${TAR_FILES}

clean:
	rm -fv *.o *.gch *.exe* ${TEST_NAME}

.PHONY: clean all tar