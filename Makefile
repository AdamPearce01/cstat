GCC=g++
CFLAGS=-g -Wall
OBJ=char_type.o token.o cpp_stat.o

all: cstat

cstat: $(OBJ)
		$(GCC) $(CFLAGS) -o cstat $(OBJ)

cpp_stat.o: cpp_stat.h cpp_stat.cpp
		$(GCC) $(FLAGS) -c cpp_stat.cpp

token.o: token.h token.cpp
		$(GCC) $(CFLAGS) -c token.cpp

char_type.o: char_type.h char_type.cpp
		$(GCC) $(CFLAGS) -c char_type.cpp


clean:
	rm cstat *.o
