all: hw7
hw7: mainIterator.o atom.o list.o struct.o iterator.h utIterator.h
ifeq ($(OS),Windows_NT)
	g++ -o hw7 mainIterator.o atom.o list.o struct.o -lgtest
else
	g++ -o hw7 mainIterator.o atom.o list.o struct.o -lgtest -lpthread
endif
atom.o: atom.cpp atom.h variable.h iterator.h
	g++ -std=gnu++0x -c atom.cpp

list.o:list.cpp list.h iterator.h variable.h
	g++ -std=gnu++0x -c list.cpp
struct.o:struct.cpp struct.h iterator.h variable.h
	g++ -std=gnu++0x -c struct.cpp

mainIterator.o: mainIterator.cpp utIterator.h
	g++ -std=gnu++0x -c mainIterator.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw7 utIterator
endif