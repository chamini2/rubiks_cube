main: clean extra HashTable Cube main.o
	g++ Cube.o extra.o HashTable.o  main.o -o $@

pdb: clean extra HashTable Cube pdb.o
	g++ Cube.o extra.o HashTable.o pdb.o  -o $@

test: clean extra HashTable Cube test.o
	g++ Cube.o extra.o HashTable.o test.o  -o $@

########################################

main.o: main.cpp
	g++ -c -std=c++11 main.cpp

pdb.o: pdb.cpp
	g++ -c -std=c++11 pdb.cpp

test.o: test.cpp
	g++ -c -std=c++11 test.cpp

########################################

Cube: Cube.cpp Cube.hpp
	g++ -c -std=c++11 Cube.cpp

HashTable: HashTable.cpp HashTable.hpp
	g++ -c -std=c++11 HashTable.cpp

Node: Node.cpp Node.hpp
	g++ -c -std=c++11 Node.cpp

extra: extra.cpp extra.hpp
	g++ -c -std=c++11 extra.cpp

########################################

clean:
	@rm main pdb test 2> /dev/null || true
	@rm *.o           2> /dev/null || true
