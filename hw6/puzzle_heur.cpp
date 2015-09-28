#include "puzzle_heur.h"

int PuzzleManhattanHeuristic::compute(const Board& b)
{
	int d = b.dim();
	int result = 0;

	for (int i = 0; i < b.size(); ++i)
	{
		if ( b[i] == 0 )
		{
			continue;
		}
		int row = i / d;
		int col = i % d;
		int rowl = b[i] / d;
		int coll = b[i] % d;

		result += abs(rowl - row) + abs(coll - col);
	}

	return result;
}

int PuzzleOutOfPlaceHeuristic::compute(const Board& b)
{
	int result = 0;

	for (int i = 0; i < b.size(); ++i)
	{
		if ( b[i] == 0 )
		{
			continue;
		}
		else if( b[i] != i ){
			result ++;
		}
	}
	return result;
}

int PuzzleBFSHeuristic::compute(const Board& b)
{
	return 0;
}