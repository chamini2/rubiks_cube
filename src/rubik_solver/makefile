rubik_solver: clean rubik_solver.o HashtableSolver
	g++  rubik_solver.o HashtableSolver.o -o $@

rubik_solver.o: rubik_solver.cpp 
	g++ -std=gnu++11 -c rubik_solver.cpp 

HashtableSolver: HashtableSolver.cpp HashtableSolver.hpp
	g++ -c -std=gnu++11 HashtableSolver.cpp 
clean:
	/bin/rm -f *.o rubik_solver
