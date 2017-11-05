all: hw5

hw5: main.o atom.o variable.o number.o list.o 

ifeq (${OS}, Windows_NT)
	g++ -o hw5 main.o atom.o variable.o number.o list.o -lgtest
else
	g++ -o hw5 main.o atom.o variable.o number.o list.o -lgtest -lpthread
endif

main.o : main.cpp scanner.h utParser.h parser.h
	g++ -std=gnu++0x -c main.cpp

atom.o: atom.cpp atom.h 
	g++ -std=c++11 -c atom.cpp

variable.o: variable.cpp variable.h
	g++ -std=c++11 -c variable.cpp

number.o: number.cpp number.h
	g++ -std=c++11 -c number.cpp

list.o: list.cpp list.h
	g++ -std=c++11 -c list.cpp




clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw5
endif
