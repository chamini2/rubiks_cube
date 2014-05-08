CC = clang
CXXFLAGS = -pg -Wall -std=c++11

# If the first argument is "test"...
ifeq (test,$(firstword $(MAKECMDGOALS)))
  # use the rest as arguments for "test"
  TEST_NUM := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  # ...and turn them into do-nothing targets
  $(eval $(TEST_NUM):;@:)
endif

main: clean extra rank Cube Set pdb.o main.o
	$(CC)++ $(CXXFLAGS) extra.o rank.o Cube.o Set.o pdb.o main.o -o $@

pdb: clean extra rank Cube Set pdb.o
	$(CC)++ $(CXXFLAGS) extra.o rank.o Cube.o Set.o pdb.o  -o $@

# use in the way: make test <number>
# where <number> is the number appended at the end of the file
# 'make test 2' would run
#     clang++ -g -Wall -std=c++11 -c extra.cpp
#     clang++ -g -Wall -std=c++11 -c rank.cpp
#     clang++ -g -Wall -std=c++11 -c Cube.cpp
#     clang++ -g -Wall -std=c++11 -c Set.cpp
#     clang++ -g -Wall -std=c++11 -c test/test2.cpp || true
#     clang++ -g -Wall -std=c++11 extra.o Cube.o Set.o rank.o test2.o -o outest2 || true
#######
# generatin the executabe 'outest2' in the 'src' folder
test: clean extra rank Cube Set test$(TEST_NUM).o
	$(CC)++ $(CXXFLAGS) extra.o Cube.o Set.o rank.o test$(TEST_NUM).o -o outest$(TEST_NUM) || true

########################################

main.o: main.cpp
	$(CC)++ $(CXXFLAGS) -c main.cpp

pdb.o: pdb.cpp pdb.hpp
	$(CC)++ $(CXXFLAGS) -c pdb.cpp

####################

test$(TEST_NUM).o: test/test$(TEST_NUM).cpp
	$(CC)++ $(CXXFLAGS) -c test/test$(TEST_NUM).cpp || true

########################################

Cube: Cube.cpp Cube.hpp
	$(CC)++ $(CXXFLAGS) -c Cube.cpp

Set: Set.cpp Set.hpp
	$(CC)++ $(CXXFLAGS) -c Set.cpp

Node: Node.cpp Node.hpp
	$(CC)++ $(CXXFLAGS) -c Node.cpp

rank: rank.cpp rank.hpp
	$(CC)++ $(CXXFLAGS) -c rank.cpp

extra: extra.cpp extra.hpp
	$(CC)++ $(CXXFLAGS) -c extra.cpp

########################################

clean:
	@rm main    2> /dev/null || true
	@rm pdb     2> /dev/null || true
	@rm outest* 2> /dev/null || true
	@rm *.o     2> /dev/null || true
