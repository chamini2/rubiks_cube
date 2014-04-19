main: clean generate extra
	g++-4.2 extra.o generate.o -o $@

generate: generate.cpp
	g++-4.2 -c generate.cpp

extra: extra.cpp
	g++-4.2 -c extra.cpp

clean:
	@rm main 2> /dev/null || true
	@rm *.o  2> /dev/null || true

