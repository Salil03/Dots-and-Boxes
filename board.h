#include <bits/stdc++.h>
using namespace std;

// Players with ability to make moves
enum class Player
{
	user = 0,
	computer = 1
};

/* Board class with helper functions
TODO:
Add scores
*/

class Board
{
public:
	class Invalid_Size
	{
	};
	class Invalid_Move
	{
	};
	Board();																	 // default initializer
	Board(int sz);																 // initializer
	void print() const;															 // print board to terminal
	void add_move(int row, int col, bool vertical, Player player, char initial); // make a move
	int get_score(const char &initial) const;									 // update score
	bool finished() const;														 // check if game finished

private:
	int size;								// size of board
	vector<vector<bool>> horizontal_dashes; // store horizontal lines
	vector<vector<bool>> vertical_dashes;	// store vertical lines
	vector<vector<char>> squares_claimed;	// store the owner of squares in grid
	void recalculate_squares(char initial); // recalculate owner of squares in grid
	friend class Computer;					// to allow algo to access horizontal_dashes, etc.
};

// By default initializes Board with size 3
Board::Board()
{
	size = 3;
	horizontal_dashes = vector<vector<bool>>(size + 1, vector<bool>(size, false));
	vertical_dashes = vector<vector<bool>>(size, vector<bool>(size + 1, false));
	squares_claimed = vector<vector<char>>(size, vector<char>(size, ' '));
}

/* Initialize Board with size = sz
Throws error for invalid size
*/
Board::Board(int sz)
{
	if (sz <= 0)
	{
		throw Invalid_Size{};
	}
	size = sz;
	horizontal_dashes = vector<vector<bool>>(size + 1, vector<bool>(size, false));
	vertical_dashes = vector<vector<bool>>(size, vector<bool>(size + 1, false));
	squares_claimed = vector<vector<char>>(size, vector<char>(size, ' '));
}

/*Print board on terminal
Ugly code, rewrite if better method found
*/
void Board::print() const
{
	static const char point = (char)254u; // character for vertex
	cout << point;
	for (int i = 0; i < size; i++)
	{
		cout << (horizontal_dashes[0][i] ? "----" : "    ") << point;
	}
	cout << "\n";
	for (int i = 0; i < size; i++)
	{
		cout << (vertical_dashes[i][0] ? "|" : " ");
		for (int j = 1; j <= size; j++)
		{
			cout << squares_claimed[i][j - 1] << "   " << (vertical_dashes[i][j] ? "|" : " ");
		}
		cout << "\n";
		cout << (vertical_dashes[i][0] ? "|" : " ");
		for (int j = 1; j <= size; j++)
		{
			cout << "    " << (vertical_dashes[i][j] ? "|" : " ");
		}
		cout << "\n"
			 << point;
		for (int j = 0; j < size; j++)
		{
			cout << (horizontal_dashes[i + 1][j] ? "----" : "    ") << point;
		}
		cout << "\n";
	}
}

/*Adds move made by Player and recalculates owners of squares*/

void Board::add_move(int row, int col, bool vertical, Player player, char initial)
{
	if (row < 0 || row > (size + vertical) || col < 0 || col > (size + !vertical)) // maybe oversmart way to check bounds
	{
		throw Invalid_Move{};
	}
	if (vertical)
	{
		if (vertical_dashes[row][col]) // throw error if move is already made
		{
			throw Invalid_Move{};
		}
		vertical_dashes[row][col] = 1;
	}
	else
	{
		if (horizontal_dashes[row][col]) // throw error if move is already made
		{
			throw Invalid_Move{};
		}
		horizontal_dashes[row][col] = 1;
	}
	recalculate_squares(initial); // recalculate squares after making move
}

/*Calculates owners of squares by checking 4 edges of square, new squares have owner with initials*/
void Board::recalculate_squares(char initial)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (squares_claimed[i][j] == ' ' && horizontal_dashes[i][j] && horizontal_dashes[i + 1][j] && vertical_dashes[i][j] && vertical_dashes[i][j + 1]) // checks if square already has a owner, then checks if all 4 edges are filled
			{
				squares_claimed[i][j] = initial;
			}
		}
	}
}

/*Returns score of player with given initial*/
int Board::get_score(const char &initial) const
{
	int sum = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			sum += (squares_claimed[i][j] == initial);
		}
	}
	return sum;
}

/*Returns true if all edges are filled and game is finishes*/
bool Board::finished() const
{
	for (int i = 0; i <= size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (!horizontal_dashes[i][j])
			{
				return false;
			}
		}
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j <= size; j++)
		{
			if (!vertical_dashes[i][j])
			{
				return false;
			}
		}
	}
	return true;
}