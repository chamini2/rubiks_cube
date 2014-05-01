rubik_solver: clean rubik_solver.o HashtableSolver Cube rank extra
	g++ -g  rubik_solver.o HashtableSolver.o Cube.o rank.o extra.o -o $@

rubik_solver.o: rubik_solver.cpp 
	g++ -g -std=gnu++11 -c rubik_solver.cpp 

HashtableSolver: HashtableSolver.cpp HashtableSolver.hpp
	g++ -g -c -std=gnu++11 HashtableSolver.cpp 

Cube: ../Cube.cpp ../Cube.hpp
	g++ -g -c -std=gnu++11 ../Cube.cpp 

rank: ../rank.cpp ../rank.hpp
	g++ -g  -c -std=c++11 ../rank.cpp

extra: ../extra.cpp ../extra.hpp
	g++ -g  -c -std=c++11 ../extra.cpp

clean:
	/bin/rm -f *.o rubik_solver
