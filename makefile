CPPflags= c++ -o
LIB = -larmadillo -llapack -lblas

all: compile execute

compile:
	${CPPflags} ./main.out main.cpp planet.cpp ${LIB}

execute:
	./main.out
