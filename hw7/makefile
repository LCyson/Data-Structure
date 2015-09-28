CXX=g++
CXXFLAGS=-g -Wall -std=c++11
# Uncomment for parser DEBUG
DEFS=-DDEBUG

OBJS=backtracking.o

all: backtracking

backtracking: $(OBJS)
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ $(OBJS)

backtracking.o: backtracking.cpp rbbst.h bst.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c backtracking.cpp

clean:
	rm -f *.o puzzle