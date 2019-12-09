CXX = mpiCC
CXXFLAGS = -Wall -g

SRCS = main.cc gamemaster.cc guesser.cpp util.cpp
OBJS = $(subst .cc,.o,$(SRCS))

build: $(OBJS)
	$(CXX) $(CXXFLAGS) -o mastermind $(OBJS)

main.o: main.cpp gamemaster.h

gamemaster.o: gamemaster.h util.h

guesser.o: guesser.h util.h

util.o: util.h

clean:
	rm $(OBJS) mastermind tests

tests: tests.o gamemaster.o guesser.o
	$(CXX) $(CXXFLAGS) -o tests tests.o gamemaster.o util.o
	./tests

tests.o: tests.cpp catch.hpp
