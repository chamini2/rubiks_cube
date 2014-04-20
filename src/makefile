top: clean extra Cube main HashTable
	g++ extra.o HashTable.o Cube.o main.o -o main

main: main.cpp
	g++ -c main.cpp

Cube: Cube.cpp Cube.hpp
	g++ -c Cube.cpp

HashTable: HashTable.cpp HashTable.hpp
	g++ -c -std=gnu++11 HashTable.cpp

extra: extra.cpp extra.hpp
	g++ -c extra.cpp

clean:
	@rm main 2> /dev/null || true
	@rm *.o  2> /dev/null || true

