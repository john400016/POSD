all: hw2

hw2: main.o atom.o variable.o number.o

ifeq (${OS}, Windows_NT)
	g++ -o hw2 main.o atom.o variable.o number.o -lgtest
else
	g++ -o hw2 main.o atom.o variable.o number.o -lgtest -lpthread
endif

main.o : main.cpp utTerm.h
	g++ -std=gnu++0x -c main.cpp

atom.o: atom.cpp atom.h
	g++ -std=c++11 -c atom.cpp

variable.o: variable.cpp variable.h
		g++ -std=c++11 -c variable.cpp

number.o: number.cpp number.h
		g++ -std=c++11 -c number.cpp

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw2
endif
