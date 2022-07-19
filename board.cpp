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
	Board();													   // default initializer
	Board(int sz);												   // initializer
	void print() const;											   // print board to terminal
	void add_move(int row, int col, bool vertical, Player player); // make a move

private:
	int size;								 // size of board
	vector<vector<bool>> horizontal_dashes;	 // store horizontal lines
	vector<vector<bool>> vertical_dashes;	 // store vertical lines
	vector<vector<char>> squares_claimed;	 // store the owner of squares in grid
	void recalculate_squares(Player player); // recalculate owner of squares in grid
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

void Board::add_move(int row, int col, bool vertical, Player player)
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
	recalculate_squares(player); // recalculate squares after making move
}

/*calculates owners of squares by checking 4 edges of square*/
void Board::recalculate_squares(Player player)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (squares_claimed[i][j] == ' ' && horizontal_dashes[i][j] && horizontal_dashes[i + 1][j] && vertical_dashes[i][j] && vertical_dashes[i][j + 1]) // checks if square already has a owner, then checks if all 4 edges are filled
			{
				if (player == Player::user)
				{
					squares_claimed[i][j] = 'U';
				}
				else
				{
					squares_claimed[i][j] = 'C';
				}
			}
		}
	}
}

int main()
{
	Board game{3};
	game.add_move(0, 0, 0, Player::user);
	game.add_move(1, 2, 0, Player::user);
	game.add_move(0, 0, 1, Player::user);
	game.add_move(2, 2, 1, Player::user);
	game.add_move(2, 0, 1, Player::user);
	game.add_move(2, 3, 1, Player::user);
	game.add_move(3, 1, 0, Player::user);
	game.add_move(1, 0, 0, Player::user);
	game.add_move(0, 1, 1, Player::user);
	game.add_move(0, 1, 0, Player::user);
	game.add_move(0, 2, 1, Player::user);
	game.add_move(1, 1, 0, Player::computer);
	game.add_move(2, 1, 1, Player::computer);
	game.add_move(2, 1, 0, Player::user);
	game.print();
}