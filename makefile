all: hw3

hw3: main.o atom.o variable.o term.o number.o

ifeq (${OS}, Windows_NT)
	g++ -o hw3 main.o atom.o variable.o term.o number.o -lgtest
else
	g++ -o hw3 main.o atom.o variable.o term.o number.o -lgtest -lpthread
endif

main.o : main.cpp utStruct.h struct.h
	g++ -std=gnu++0x -c main.cpp

atom.o: atom.cpp atom.h
	g++ -std=c++11 -c atom.cpp

term.o: term.cpp term.h
	g++ -std=c++11 -c term.cpp

variable.o: variable.cpp variable.h
	g++ -std=c++11 -c variable.cpp

number.o: number.cpp number.h
	g++ -std=c++11 -c number.cpp

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw3
endif
