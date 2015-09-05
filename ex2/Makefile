CC = g++
C_FLAGS = -std=c++11 -Wall -Wextra -g
TAR_NAME = ex2.tar
TAR_FILES = README Makefile extension.pdf
VALGRIND_FLAGS = --leak-check=full --show-possibly-lost=yes --show-reachable=yes --undef-value-errors=yes

MIR: MIR.o Song.o Parser.o VocalSong.o InstrumentalSong.o
	${CC} ${C_FLAGS} MIR.o Song.o Parser.o VocalSong.o InstrumentalSong.o -o MIR

MIR.o: MIR.cpp Song.h Parser.h
	${CC} ${C_FLAGS} -c MIR.cpp

Song.o: Song.h Song.cpp
	${CC} ${C_FLAGS} -c Song.cpp

VocalSong.o: VocalSong.cpp VocalSong.h Song.h
	${CC} ${C_FLAGS} -c VocalSong.cpp

InstrumentalSong.o: InstrumentalSong.cpp InstrumentalSong.h Song.h
	${CC} ${C_FLAGS} -c InstrumentalSong.cpp

Parser.o: Parser.h Parser.cpp VocalSong.h InstrumentalSong.h
	${CC} ${C_FLAGS} -c Parser.cpp

tar: ${TAR_FILES}
	tar -cvf ${TAR_NAME} ${TAR_FILES}

all: MIR tar
	echo made all

clean:
	rm -fv *.o *.exe*

.PHONY: all clean tar