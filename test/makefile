top: clean extra Cube hash_test HashTable
	g++ extra.o HashTable.o Cube.o hash_test.o -o test

hash_test: hash_test.cpp hash_test.hpp
	g++ -std=gnu++11 -c hash_test.cpp

Cube: ../src/Cube.cpp ../src/Cube.hpp
	g++ -c ../src/Cube.cpp

HashTable: ../src/HashTable.cpp ../src/HashTable.hpp
	g++ -c -std=gnu++11 ../src/HashTable.cpp

extra: ../src/extra.cpp ../src/extra.hpp
	g++ -c ../src/extra.cpp

clean:
	@rm test 2> /dev/null || true
	@rm *.o  2> /dev/null || true

