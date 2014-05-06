ROOT_DIR = ..

rubik_solver: clean rubik_solver.o HashtableSolver Cube rank extra
	g++ -g  rubik_solver.o HashtableSolver.o Cube.o rank.o extra.o -o $@

rubik_solver.o: rubik_solver.cpp rubik_solver.hpp
	g++ -g -std=gnu++11 -c rubik_solver.cpp 

HashtableSolver: HashtableSolver.cpp HashtableSolver.hpp
	g++ -g -c -std=gnu++11 HashtableSolver.cpp 

Cube: $(ROOT_DIR)/Cube.cpp $(ROOT_DIR)/Cube.hpp
	g++ -g -c -std=gnu++11 $(ROOT_DIR)/Cube.cpp 

rank: $(ROOT_DIR)/rank.cpp $(ROOT_DIR)/rank.hpp
	g++ -g  -c -std=c++11 $(ROOT_DIR)/rank.cpp

extra: $(ROOT_DIR)/extra.cpp $(ROOT_DIR)/extra.hpp
	g++ -g  -c -std=c++11 $(ROOT_DIR)/extra.cpp

clean:
	/bin/rm -f *.o rubik_solver
