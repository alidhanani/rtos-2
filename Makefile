CXX = mpiCC
CXXFLAGS = -Wall -g

SRCS = main.cpp gamemaster.cpp guesser.cpp util.cpp
OBJS = $(subst .cpp,.o,$(SRCS))

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
