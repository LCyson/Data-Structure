#include <iostream>
#include <cstdlib>
#include <deque>
#include <string>
#include <deque>
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"
#include "puzzle_move.h"

using namespace std;

int main(int argc, char *argv[])
{
  if(argc < 5){
    cerr << "Usage: ./puzzle size initMoves seed heur" << endl;
    return 1;
  }

  int p1 = atoi(argv[1]);
  int p2 = atoi(argv[2]);
  int p3 = atoi(argv[3]);
  int heur = atoi(argv[4]);
  PuzzleHeuristic* h;
  PuzzleManhattanHeuristic* h1 = new PuzzleManhattanHeuristic;
  PuzzleOutOfPlaceHeuristic* h2 = new PuzzleOutOfPlaceHeuristic;
  PuzzleBFSHeuristic* h3 = new PuzzleBFSHeuristic;

  if ( heur == 2 )
  {
  	h = h1;
  }
  if ( heur == 0 )
  {
  	h = h3;
  }
  if ( heur == 1 )
  {
  	h = h2;
  }

  Board b(p1, p2, p3);


  while( !b.solved() )
  {
	cout<< b;
	cout<<"Enter tile number to move or -1 for a cheat: \n";
	int temp;
	cin >> temp;


	while ( cin.fail() || temp == 0 || temp < -1 || temp >= p1 * p1)
	{
		cout << "Please enter a correct interger" << endl;
		cin >> temp;
	}

	if ( temp == -1 )
	{
		cout<< "Try this:";

		PuzzleSolver solver( b, h );
		solver.run();
		deque<int> answer = solver.getSolution();
		int expansions = solver.getNumExpansions();

		for (unsigned int i = 0; i < answer.size(); ++i)
		{
			cout<< answer[i] << " ";
		}
			cout<< endl;
			cout<< "(Expansions: " << expansions << ")"<< endl;
		continue;
	}

	b.move(temp);
  }


  delete h1;
  delete h2;
  delete h3;
  return 0;
}
