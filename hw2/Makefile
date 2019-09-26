all: directory interpreter

MKDIR_P = mkdir -p 
OUT_DIR = interpreter/bin
directory: ${OUT_DIR}
${OUT_DIR}:
	${MKDIR_P} ${OUT_DIR}

interpreter: interpreter/main.cpp interpreter/bin/arithmetic.o interpreter/bin/boolean.o interpreter/bin/command.o interpreter/bin/interpreter.o
	g++ -g -Wall -std=c++11 interpreter/main.cpp interpreter/bin/arithmetic.o interpreter/bin/boolean.o interpreter/bin/command.o interpreter/bin/interpreter.o -o basic_interpreter

interpreter/bin/interpreter.o: interpreter/interpreter.h interpreter/interpreter.cpp
	g++ -g -Wall -std=c++11 -c interpreter/interpreter.cpp -o interpreter/bin/interpreter.o
	
interpreter/bin/arithmetic.o: interpreter/arithmetic.h interpreter/arithmetic.cpp
	g++ -g -Wall -std=c++11 -c interpreter/arithmetic.cpp -o interpreter/bin/arithmetic.o

interpreter/bin/boolean.o: interpreter/boolean.h interpreter/boolean.cpp
	g++ -g -Wall -std=c++11 -c interpreter/boolean.cpp -o interpreter/bin/boolean.o

interpreter/bin/command.o: interpreter/command.h interpreter/command.cpp
	g++ -g -Wall -std=c++11 -c interpreter/command.cpp -o interpreter/bin/command.o