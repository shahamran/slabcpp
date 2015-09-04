CC = g++
C_FLAGS = -std=c++11 -Wall -Wextra -g
TAR_NAME = ex2.tar
TAR_FILES = README Makefile
VALGRIND_FLAGS = --leak-check=full --show-possibly-lost=yes --show-reachable=yes --undef-value-errors=yes

MIR: MIR.o
	${CC} ${C_FLAGS} MIR.o Song.o Parser.o -o MIR

MIR.o: MIR.cpp Song.h Parser.h
	${CC} ${C_FLAGS} -c MIR.cpp Song.h Parser.h -o MIR.o

Song.o: Song.h Song.cpp
	${CC} ${C_FLAGS} -c Song.cpp Song.h -o Song.o

Parser.o: Parser.h Parser.cpp VocalSong.h InstrumentalSong.h
	${CC} ${C_FLAGS} -c Parser.cpp Parser.h -o Parser.o

clean:
	rm -fv *.o *.exe*

.PHONY: all clean