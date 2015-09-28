#include "puzzle_move.h"

PuzzleMove::PuzzleMove(Board* board)
{
  b = board;
  g = 0;
  prev = NULL;
}

PuzzleMove::PuzzleMove(int tile, Board* board, PuzzleMove *parent)
{
  b = board;
  tileMove = tile;
  prev = parent;
  g = parent->g + 1;
}

PuzzleMove::~PuzzleMove()
{

}
