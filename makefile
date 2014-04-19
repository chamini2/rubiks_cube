top: clean extra Cube main
	g++ extra.o Cube.o main.o -o main

main: main.cpp main.hpp
	g++ -c main.cpp

Cube: Cube.cpp Cube.hpp
	g++ -c Cube.cpp

extra: extra.cpp extra.hpp
	g++ -c extra.cpp

clean:
	@rm main 2> /dev/null || true
	@rm *.o  2> /dev/null || true

