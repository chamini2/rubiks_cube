top: clean extra HashTable Cube main
	g++ extra.o HashTable.o Cube.o main.o -o main

main: main.cpp
	g++ -c -std=c++0x -stdlib=libc++ main.cpp

Cube: Cube.cpp Cube.hpp
	g++ -c -std=c++0x -stdlib=libc++ Cube.cpp

HashTable: HashTable.cpp HashTable.hpp
	g++ -c -std=gnu++11 HashTable.cpp

extra: extra.cpp extra.hpp
	g++ -c extra.cpp

pdb: clean extra HashTable Cube corners
	g++ extra.o HashTable.o Cube.o cornersPDB.o -o pdb

corners: cornersPDB.cpp
	g++ -c -std=c++0x -stdlib=libc++ cornersPDB.cpp

clean:
	@rm main pdb 2> /dev/null || true
	@rm *.o      2> /dev/null || true
