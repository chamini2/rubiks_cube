CC = clang
CXXFLAGS = -g -Wall -std=c++11

main: clean extra Cube Set EdgeSet main.o
	$(CC)++ $(CXXFLAGS) extra.o Cube.o EdgeSet.o Set.o  main.o -o $@

pdb: clean extra rank Cube Set pdb.o
	$(CC)++ $(CXXFLAGS) extra.o rank.o Cube.o Set.o pdb.o  -o $@

tests: clean extra rank Cube EdgeSet.o Set test1.o
	# $(CC)++ $(CXXFLAGS) extra.o rank.o test0.o -o outest0 || true
	$(CC)++ $(CXXFLAGS) extra.o Cube.o rank.o test1.o -o outest1 || true
	# $(CC)++ $(CXXFLAGS) extra.o rank.o test2.o -o outest2 || true
	# $(CC)++ $(CXXFLAGS) extra.o Cube.o rank.o test3.o -o outest3 || true
	# $(CC)++ $(CXXFLAGS) extra.o Cube.o rank.o test4.o -o outest4 || true
	# $(CC)++ $(CXXFLAGS) extra.o Cube.o rank.o test5.o -o outest5 || true
	# $(CC)++ $(CXXFLAGS) extra.o Cube.o Set.o rank.o test6.o -o outest6 || true

########################################

main.o: main.cpp
	$(CC)++ $(CXXFLAGS) -c main.cpp

pdb.o: pdb.cpp
	$(CC)++ $(CXXFLAGS) -c pdb.cpp

####################

test0.o: test/test0.cpp
	# $(CC)++ $(CXXFLAGS) -c test/test0.cpp || true

test1.o: test/test1.cpp
	$(CC)++ $(CXXFLAGS) -c test/test1.cpp

test2.o: test/test2.cpp
	# $(CC)++ $(CXXFLAGS) -c test/test2.cpp || true

test3.o: test/test3.cpp
	# $(CC)++ $(CXXFLAGS) -c test/test3.cpp || true

test4.o: test/test4.cpp
	# $(CC)++ $(CXXFLAGS) -c test/test4.cpp || true

test5.o: test/test5.cpp
	# $(CC)++ $(CXXFLAGS) -c test/test5.cpp || true

test6.o: test/test6.cpp
	# $(CC)++ $(CXXFLAGS) -c test/test6.cpp || true

####################

########################################

Cube: Cube.cpp Cube.hpp
	$(CC)++ $(CXXFLAGS) -c Cube.cpp

Set: Set.cpp Set.hpp
	$(CC)++ $(CXXFLAGS) -c Set.cpp

EdgeSet: EdgeSet.cpp EdgeSet.hpp
	$(CC)++ $(CXXFLAGS) -c EdgeSet.cpp

Node: Node.cpp Node.hpp
	$(CC)++ $(CXXFLAGS) -c Node.cpp

rank: rank.cpp rank.hpp
	$(CC)++ $(CXXFLAGS) -c rank.cpp

extra: extra.cpp extra.hpp
	$(CC)++ $(CXXFLAGS) -c extra.cpp

########################################

clean:
	@rm main  2> /dev/null || true
	@rm pdb   2> /dev/null || true
	@rm outest* 2> /dev/null || true
	@rm *.o   2> /dev/null || true
