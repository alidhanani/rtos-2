CXX = mpiCC
CXXFLAGS = -Wall -g -std=c++17
LDLIBS = -lboost_mpi -lboost_serialization

SRCS = gamemaster.cpp guesser.cpp util.cpp colorsequence.cpp messages.cpp
OBJS = $(subst .cpp,.o,$(SRCS))

all: tests build

build: main.o $(OBJS)
	$(CXX) $(CXXFLAGS) -o mastermind main.o $(OBJS) $(LDLIBS)

main.o: main.cpp gamemaster.h guesser.h messages.h

gamemaster.o: gamemaster.h colorsequence.h

guesser.o: guesser.h colorsequence.h

util.o: util.h

colorsequence.o: colorsequence.h util.h

messages.o: messages.h util.h

clean:
	rm $(OBJS) main.o tests.o mastermind tests

tests: tests.o $(OBJS)
	$(CXX) $(CXXFLAGS) -o tests tests.o $(OBJS)
	./tests

tests.o: tests.cpp catch.hpp
