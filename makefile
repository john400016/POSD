all: hw8 shell

hw8: mainExp.o term.o atom.o number.o struct.o variable.o number.o list.o global.o parser.o scanner.o shell.o exp.o
ifeq ($(OS), Windows_NT)
	g++ -o hw8 mainExp.o term.o atom.o struct.o variable.o number.o list.o global.o parser.o scanner.o shell.o exp.o -lgtest
else
	g++ -o hw8 mainExp.o term.o atom.o struct.o variable.o number.o list.o global.o parser.o scanner.o shell.o exp.o -lgtest -lpthread
endif

shell: mainShell.o term.o atom.o number.o struct.o variable.o number.o list.o global.o parser.o scanner.o	shell.o exp.o
ifeq ($(OS), Windows_NT)
	g++ -std=gnu++0x -o shell mainShell.o term.o atom.o struct.o variable.o number.o list.o global.o parser.o scanner.o shell.o exp.o -lgtest
else
	g++ -std=gnu++0x -o shell mainShell.o term.o atom.o struct.o variable.o number.o list.o global.o parser.o scanner.o shell.o exp.o -lgtest -lpthread
endif

mainShell.o:mainShell.cpp exp.h
	g++ -std=gnu++0x -c mainShell.cpp

mainExp.o:mainExp.cpp expression.h exception.h exp.h
	g++ -std=gnu++0x -c mainExp.cpp

term.o:term.h term.cpp
	g++ -std=gnu++0x -c term.cpp

atom.o:atom.h atom.cpp
	g++ -std=gnu++0x -c atom.cpp

number.o:number.h number.cpp
	g++ -std=gnu++0x -c number.cpp

struct.o:struct.h struct.cpp
	g++ -std=gnu++0x -c struct.cpp

list.o:list.h list.cpp
	g++ -std=gnu++0x -c list.cpp

global.o:global.h global.cpp
	g++ -std=gnu++0x -c global.cpp

variable.o:variable.h variable.cpp
	g++ -std=gnu++0x -c variable.cpp

scanner.o: scanner.h scanner.cpp
	g++ -std=gnu++0x -c scanner.cpp

parser.o: parser.h parser.cpp
	g++ -std=gnu++0x -c parser.cpp

shell.o: shell.h shell.cpp
	g++ -std=gnu++0x -c shell.cpp

exp.o: exp.h exp.cpp
	g++ -std=gnu++0x -c exp.cpp
	
clean:
ifeq (${OS}, Windows_NT)
	del hw8 *.o
else
	rm shell hw8 *.o
endif