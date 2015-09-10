CPPFLAGS=-std=c++11 -Wall -Wextra -Wvla -O -DNDEBUG

.SUFFIXES:

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $<

GMD: GenericMatrixDriver.o  Complex.o Matrix.hpp MatrixExceptions.o
	$(CXX) $(CPPFLAGS) $^ -o $@

PAR: ParallelChecker.o Complex.o Matrix.hpp MatrixExceptions.o
	$(CXX) $(CPPFLAGS) $^ -o $@ -lpthread

clean:
	rm -rf *.o *.gch $(EXEC) $(TARNAME) PAR GMD

.PHONY: clean
