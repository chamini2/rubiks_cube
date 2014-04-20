main: clean extra HashTable Cube main.o
	g++ extra.o HashTable.o Cube.o main.o -o $@

pdb: clean extra HashTable Cube pdb.o
	g++ extra.o HashTable.o Cube.o pdb.o -o $@

########################################

main.o: main.cpp
	g++ -c -std=c++0x -stdlib=libc++ main.cpp

pdb.o: pdb.cpp
	g++ -c -std=c++0x -stdlib=libc++ pdb.cpp

########################################

Cube: Cube.cpp Cube.hpp
	g++ -c -std=c++0x -stdlib=libc++ Cube.cpp

HashTable: HashTable.cpp HashTable.hpp
	g++ -c -std=gnu++11 HashTable.cpp

extra: extra.cpp extra.hpp
	g++ -c extra.cpp

########################################

clean:
	@rm main pdb 2> /dev/null || true
	@rm *.o      2> /dev/null || true
