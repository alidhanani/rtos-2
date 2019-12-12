CXX = mpiCC
CXXFLAGS = -Wall -g -std=c++17
LDLIBS = -lboost_mpi -lboost_serialization

SRCS = gamemaster.cpp guesser.cpp colorsequence.cpp respondedguess.cpp proposedguess.cpp
OBJS = $(subst .cpp,.o,$(SRCS))

all: tests build

build: main.o $(OBJS)
	$(CXX) $(CXXFLAGS) -o mastermind main.o $(OBJS) $(LDLIBS)

main.o: main.cpp gamemaster.h guesser.h

gamemaster.o: gamemaster.h colorsequence.h

guesser.o: guesser.h colorsequence.h

respondedguess.o: respondedguess.h colorsequence.h

proposedguess.o: proposedguess.h colorsequence.h

colorsequence.o: colorsequence.h

messages.o: messages.h

clean:
	rm $(OBJS) main.o tests.o mastermind tests

tests: tests.o colorsequence.o
	$(CXX) $(CXXFLAGS) -o tests tests.o colorsequence.o
	./tests

tests.o: tests.cpp catch.hpp
