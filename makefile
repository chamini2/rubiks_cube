top: clean extra Cube main
	g++-4.2 extra.o Cube.o main.o -o main

main: main.cpp main.hpp
	g++-4.2 -c main.cpp

Cube: Cube.cpp Cube.hpp
	g++-4.2 -c Cube.cpp

extra: extra.cpp extra.hpp
	g++-4.2 -c extra.cpp

clean:
	@rm main 2> /dev/null || true
	@rm *.o  2> /dev/null || true

