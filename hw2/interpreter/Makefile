all: interpreter

interpreter: main.cpp arithmetic.o command.o interpreter.o boolean.o
	g++ -g -Wall -std=c++11 main.cpp arithmetic.o command.o boolean.o interpreter.o -o basic_interpreter

arithmetic.o: arithmetic.h arithmetic.cpp
	g++ -g -Wall -std=c++11 -c arithmetic.cpp -o arithmetic.o

command.o: command.h command.cpp 
	g++ -g -Wall -std=c++11 -c command.cpp -o command.o

boolean.o: boolean.h boolean.cpp
	g++ -g -Wall -std=c++11 -c boolean.cpp -o boolean.o