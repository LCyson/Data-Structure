#include "puzzle_solver.h"

PuzzleSolver::PuzzleSolver(const Board &b, PuzzleHeuristic* ph):_b(b)
{
	_ph = ph;
	_expansions = 0;
}

PuzzleSolver::~PuzzleSolver()
{
	for (std::set<PuzzleMove*>::iterator i = for_Delete.begin(); i != for_Delete.end(); ++i)
		{
			Board* temp = (*i)->b;
			delete temp;
			delete *i;
		}	
}

void PuzzleSolver::run()
{
	PuzzleMoveScoreComp open_comp;
	bool flag = false;
	PuzzleMoveSet close_list;
  	Heap<PuzzleMove*, PuzzleMoveScoreComp> open_list(2, open_comp);

  	PuzzleMove S(&_b);
  	S.h = _ph->compute(*(S.b));
	open_list.push(&S);


	while( !open_list.empty() )
	{	
		PuzzleMove* next_puzzle = open_list.top();
		Board* next_board = next_puzzle->b;	
		open_list.pop();
		close_list.insert( next_puzzle );	
		std::map<int, Board*> PotentialMove = next_board->potentialMoves();


		if ( (next_puzzle->b)->solved() )
		{
			for_Delete.insert( next_puzzle );
			while(next_puzzle->prev != NULL)
			{
				int temp = next_puzzle->tileMove;
				_solution.push_front( temp );
				next_puzzle = next_puzzle->prev;
			}
				break ;
		}


		for (std::map<int, Board*>::iterator i = PotentialMove.begin(); 
			i != PotentialMove.end(); ++i)
		{
			PuzzleMove* new_move = new PuzzleMove( i->first, i->second, next_puzzle);
			for_Delete.insert(new_move);

			//compute h and g value
			new_move->h = _ph->compute( *(new_move->b) );

			if ( close_list.find( new_move ) != close_list.end() )  flag = true; 

			if ( !flag )
			{
				open_list.push( new_move );	
				close_list.insert( new_move );
				_expansions++;	
			}
			flag = false;
		}
	}
}

std::deque<int> PuzzleSolver::getSolution()
{
	return _solution;
}

int PuzzleSolver::getNumExpansions()
{
	return _expansions;
}