CXXFLAGS = -g -Wall

main: clean extra Cube HashTable main.o
	g++ $(CXXFLAGS) extra.o Cube.o HashTable.o  main.o -o $@

pdb: clean extra rank Cube HashTable pdb.o
	g++ $(CXXFLAGS) extra.o rank.o Cube.o HashTable.o pdb.o  -o $@

tests: clean extra rank test0.o test1.o test2.o
	g++ $(CXXFLAGS) extra.o rank.o test0.o -o outest0 || true
	g++ $(CXXFLAGS) extra.o rank.o test1.o -o outest1 || true
	g++ $(CXXFLAGS) extra.o rank.o test2.o -o outest2 || true

########################################

main.o: main.cpp
	g++ $(CXXFLAGS) -c -std=c++11 main.cpp

pdb.o: pdb.cpp
	g++ $(CXXFLAGS) -c -std=c++11 pdb.cpp

####################

test0.o: test/test0.cpp
	g++ $(CXXFLAGS) -c -std=c++11 test/test0.cpp

test1.o: test/test1.cpp
	g++ $(CXXFLAGS) -c -std=c++11 test/test1.cpp

test2.o: test/test2.cpp
	g++ $(CXXFLAGS) -c -std=c++11 test/test2.cpp

####################

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
	@rm main  2> /dev/null || true
	@rm pdb   2> /dev/null || true
	@rm outest* 2> /dev/null || true
	@rm *.o   2> /dev/null || true
