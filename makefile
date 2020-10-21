CPPflags= c++ -O3 -o
LIB = -larmadillo -llapack -lblas

all: compile execute

compile:
	${CPPflags} ./main.out main.cpp planet.cpp diff_solver.cpp ${LIB}


execute:
	./main.out
