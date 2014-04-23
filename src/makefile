CXXFLAGS = -g -Wall

main: clean extra Cube HashTable main.o
	g++ $(CXXFLAGS) extra.o Cube.o HashTable.o  main.o -o $@

pdb: clean extra rank Cube HashTable pdb.o
	g++ $(CXXFLAGS) extra.o rank.o Cube.o HashTable.o pdb.o  -o $@

test: clean extra Cube HashTable test.o
	g++ $(CXXFLAGS) extra.o Cube.o HashTable.o test.o  -o $@

########################################

main.o: main.cpp
	g++ $(CXXFLAGS) -c -std=c++11 main.cpp

pdb.o: pdb.cpp
	g++ $(CXXFLAGS) -c -std=c++11 pdb.cpp

test.o: test.cpp
	g++ $(CXXFLAGS) -c -std=c++11 test.cpp

########################################

Cube: Cube.cpp Cube.hpp
	g++ $(CXXFLAGS) -c -std=c++11 Cube.cpp

HashTable: HashTable.cpp HashTable.hpp
	g++ $(CXXFLAGS) -c -std=c++11 HashTable.cpp

Node: Node.cpp Node.hpp
	g++ $(CXXFLAGS) -c -std=c++11 Node.cpp

rank: rank.cpp rank.hpp
	g++ $(CXXFLAGS) -c -std=c++11 rank.cpp

extra: extra.cpp extra.hpp
	g++ $(CXXFLAGS) -c -std=c++11 extra.cpp

########################################

clean:
	@rm main pdb test 2> /dev/null || true
	@rm *.o           2> /dev/null || true
