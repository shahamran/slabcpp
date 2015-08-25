CC = g++
C_FLAGS = -std=c++11 -Wall -Wextra -g
TAR_NAME = ex1.tar
TAR_FILES = IntMatrix.h IntMatrix.cpp IntMatrixDriver.cpp Makefile
VALGRIND_FLAGS = --leak-check=full --show-possibly-lost=yes --show-reachable=yes --undef-value-errors=yes

ValgrindTest: IntMatrixMainDriver
	valgrind ${VALGRIND_FLAGS} ./IntMatrixMainDriver

all: IntMatrix IntMatrixMainDriver tar
	echo all

IntMatrixMainDriver: IntMatrixDriver.o IntMatrix.o
	${CC} ${C_FLAGS} IntMatrixDriver.o IntMatrix.o -o IntMatrixMainDriver

IntMatrixDriver.o: IntMatrixDriver.cpp IntMatrix.h
	${CC} ${C_FLAGS} -c IntMatrixDriver.cpp

tar: ${TAR_FILES}
	tar -cvf ${TAR_NAME} ${TAR_FILES}

IntMatrix: IntMatrix.o
	echo IntMatrix

IntMatrix.o: IntMatrix.h IntMatrix.cpp
	${CC} ${C_FLAGS} -c IntMatrix.cpp

clean:
	rm -fv *.o IntMatrixMainDriver *.exe*

.PHONY: clean all IntMatrix tar ValgrindTest