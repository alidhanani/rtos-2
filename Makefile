CXX = mpiCC
CXXFLAGS = -Wall -g

SRCS = main.cc gamemaster.cc
OBJS = $(subst .cc,.o,$(SRCS))

build: $(OBJS)
	$(CXX) $(CXXFLAGS) -o mastermind main.o gamemaster.o

main.o: main.cpp gamemaster.h

gamemaster.o: gamemaster.h

clean:
	rm $(OBJS) mastermind
