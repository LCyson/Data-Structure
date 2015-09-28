CXX=g++
CXXFLAGS=-g -Wall -std=c++11
# Uncomment for parser DEBUG
DEFS=-DDEBUG

OBJS=puzzle.o board.o puzzle_heur.o puzzle_solver.o puzzle_move.o

all: puzzle

puzzle: $(OBJS)
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ $(OBJS)

puzzle.o: puzzle.cpp board.h puzzle_heur.h puzzle_solver.h puzzle_move.h heap.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c puzzle.cpp
board.o: board.cpp board.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c board.cpp
puzzle_heur.o: puzzle_heur.cpp puzzle_heur.h board.h 
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c puzzle_heur.cpp
puzzle_solver.o: puzzle_solver.cpp puzzle_solver.h board.h puzzle_heur.h puzzle_move.h heap.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c puzzle_solver.cpp
puzzle_move.o: puzzle_move.cpp puzzle_move.h board.h puzzle_heur.h 
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c puzzle_move.cpp



clean:
	rm -f *.o puzzle