CC = g++

C_FLAGS = -std=c++11 -Wall -Wextra
TAR_NAME = ex3.tar
TAR_FILES = Matrix.hpp
VALGRIND_FLAGS = --leak-check=full --show-possibly-lost=yes --show-reachable=yes --undef-value-errors=yes



tar: ${TAR_FILES}
	tar -cvf ${TAR_NAME} ${TAR_FILES}

clean:
	rm -fv *.o *.gch *.exe*

.PHONY: clean all tar