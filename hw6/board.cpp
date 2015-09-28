#include <iostream>
#include <iomanip>
#include <map>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include "board.h"
using namespace std;


Board::Board(int dim, int numInitMoves, int seed )
{
  _size = dim*dim;
  _tiles = new int[_size];
  srand(seed);
  for(int i=0; i < _size; i++){
    _tiles[i] = i;
  }
  int blankLoc = 0;
  while(numInitMoves > 0){
    int r = rand()%4;
    int randNeighbor = -1;
    if(r == 0){
      int n = blankLoc - dim;
      if(n >= 0){
	randNeighbor = n;
      }
    }
    else if(r == 1){
      int w = blankLoc - 1;
      if(blankLoc % dim != 0){
	randNeighbor = w;
      }
    }
    else if(r == 2){
      int s = blankLoc + dim;
      if(s  < _size){
	randNeighbor = s;
      }
    }
    else {
      int e = blankLoc + 1;
      if(blankLoc % dim != dim-1){
	randNeighbor = e;
      }
    }
    if(randNeighbor > -1){
      _tiles[blankLoc] = _tiles[randNeighbor];
      _tiles[randNeighbor] = 0;
      blankLoc = randNeighbor;
      numInitMoves--;
    }
  }
}

Board::Board(const Board& b)
{
  this->_size = b.size();
  this->_tiles = new int[_size];

  for (int i = 0; i < b.size(); ++i)
  {
    _tiles[i] = b[i];
  }
}

Board::~Board()
{
  delete _tiles;
}


void Board::move(int tile)
{
  int side_dim = dim();
  int tr, tc, br, bc;

  // find tile row and column
  int i=-1;
  while(_tiles[++i] != tile);

  tr = i / side_dim; 
  tc = i % side_dim;

  // find blank row and column
  int j=-1;
  while(_tiles[++j] != 0);

  br = j / side_dim;
  bc = j % side_dim;

  if( abs(static_cast<double>(tr-br)) + abs(static_cast<double>(tc-bc)) != 1){
    cout << "Invalid move of tile " << tile << " at ";
    cout << tr << "," << tc << " and blank spot at ";
    cout << br << "," << bc << endl;
    return;
  }
  // Swap tile and blank spot
  _tiles[j] = tile;
  _tiles[i] = 0;
}

// Generate new boards representing all the potential moves of tiles into 
// the current blank tile location. The returned map should have
// the key as the tile moved and the value as a new Board object with the
// configuration reflecting the move of that tile into the blank spot
map<int, Board*> Board::potentialMoves() const
{
  map<int, Board*> result;
  int side_dim = dim();
  int blankLoc=-1;
  while(_tiles[++blankLoc] != 0);

  int br = blankLoc / side_dim;
  int bc = blankLoc % side_dim;

  if ( bc - 1 >= 0 )
  {    
    int move = blankLoc - 1;
    Board* new_board = new Board(*this);
    new_board->move(_tiles[move]);

    result.insert(make_pair(_tiles[move], new_board));
  }
  if ( br - 1 >= 0 )
  {    
    int move = blankLoc - side_dim;
    Board* new_board = new Board(*this);
    new_board->move(_tiles[move]);

    result.insert(make_pair(_tiles[move], new_board));
  }
  if ( bc + 1 < side_dim )
  {    
    int move = blankLoc + 1;
    Board* new_board = new Board(*this);
    new_board->move(_tiles[move]);

    result.insert(make_pair(_tiles[move], new_board));
  }
  if ( br + 1 < side_dim )
  {    
    int move = blankLoc + side_dim;
    Board* new_board = new Board(*this);
    new_board->move(_tiles[move]);

    result.insert(make_pair(_tiles[move], new_board));
  }

  return result;
}





bool Board::solved() const
{
  for (int i = 0; i < _size; ++i)
  {
    if( _tiles[i] != i){
      return false;
    }
  }
    return true;
}


ostream& operator<<(std::ostream &os, const Board &b)
{
  int side_dim = b.dim();
  int loc = 0;
  if(side_dim == 0) return os;
  for (int i = 0; i < side_dim; ++i)
  {
    b.printRowBanner(os);
    os<< "|";
    for (int i = 0; i < side_dim; ++i)
    {
      os<< setw(2) << b[loc];
      os<< "|";
      loc++;
    }
    os<< "\n";
  }
    b.printRowBanner(os);

  return os;
}


const int& Board::operator[](int loc) const 
{ 
  return _tiles[loc]; 
}

bool Board::operator<(const Board& rhs) const
{
  for (int i = 0; i < _size; ++i)
  {
    if ((*this)[i] < rhs[i])
    {
      return true;
    }
    if ((*this)[i] > rhs[i])
    {
      return false;
    }    
  }
    return false;
}



int Board::size() const 
{ 
  return _size; 
}

int Board::dim() const
{
  return static_cast<int>(sqrt(_size));
}

void Board::printRowBanner(ostream& os) const
{
  int side_dim = dim();
  if(side_dim == 0) return;
  os << '+';
  for(int i=0; i < side_dim; i++){
    os << "--+";
  }
  os << endl;
}
