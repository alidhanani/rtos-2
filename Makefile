CXX = mpiCC
CXXFLAGS = -Wall -g

SRCS = main.cc gamemaster.cc
OBJS = $(subst .cc,.o,$(SRCS))

build: $(OBJS)
	$(CXX) $(CXXFLAGS) -o mastermind $(OBJS)

main.o: main.cpp gamemaster.h

gamemaster.o: gamemaster.h

clean:
	rm $(OBJS) mastermind tests

tests: tests.o gamemaster.o
	$(CXX) $(CXXFLAGS) -o tests tests.o gamemaster.o
	./tests

tests.o: tests.cpp catch.hpp
