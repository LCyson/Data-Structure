#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "rbbst.h"

using namespace std;

struct Rectangle {
    int ID;
	int length;
    int height;
};

int board**;
int board_length;
int board_height;
int num_tiles;
RedBlackTree<int, Rectangle > input_tree;
RedBlackTree<int, Rectangle > output_tree;


void readFile( ifstream& file )
{
	string line;
	
	getline(file, line);
	stringstream trans(line);
	trans >> board_length; trans >> board_height; 
	trans >> num_tiles;
	board = new int[board_length][board_height];

	while( getline(file, line) )
	{
		int ID; Rectangle rec; 
		stringstream trans(line);
		trans >> ID; 
		rec.ID = ID; 
		trans >> rec.length; 
		trans >> rec.height;
		input_tree.insert( make_pair(ID, rec) );
		// cout<< "insert" << ID <<endl;
	}
}

// check if row, col is a valid position to place the rectangle
bool okayPosition(int row, int col) {
	for (int i = 0; i < row; i++)
	{
		int other_row_pos = board[i];

		if (other_row_pos == col || 
			other_row_pos == col - (row - i) ||
			other_row_pos == col + (row - i))
			return false;
	}
	return true;
}

void fillBoard( int** b )
{

}

bool solveRecTiles(RedBlackTree<int, Rectangle>::iterator it) {
	if (tiles == 4) { 
		// at this point we've hit the end of the board
		cout << "Solution: ";
		for (int i = 0; i < 4; i++) {	
			cout << board[i] << " ";
		}
		cout << endl;
		return true;
	}
	else
	{
		RedBlackTree<int, Rectangle>::iterator i;
		for ( i = input_tree.begin(); i != input_tree.end() ; i++)
		{
			if (okayPosition(row, i))
			{
				fillBoard( board );
				if( solveRecTiles( ++it ) ) return true;
			}
		}
	}
	return false;
}

int main(int argc, char *argv[]){
	ifstream myfile;
  	ofstream ofile;
  	myfile.open(argv[1]);
  	ofile.open(argv[2]);

  	readFile(myfile);

  	RedBlackTree<int, Rectangle>::iterator i = input_tree.begin();
	solveRecTiles( i );

  	// for (RedBlackTree<int, Rectangle>::iterator i = input_tree.begin(); i != input_tree.end(); ++i)
  	// {
  	// 	cout<< (*i).first <<endl;
  	// }


	return 0;
}