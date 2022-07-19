#include <bits/stdc++.h>
using namespace std;

enum class Player
{
	user = 0,
	computer = 1
};

class Board
{
public:
	class Invalid_Size
	{
	};
	class Invalid_Move
	{
	};
	Board(int sz);
	void print() const;
	void add_move(int row, int col, bool orientation, Player player);

private:
	int size;
	vector<vector<bool>> horizontal_dashes;
	vector<vector<bool>> vertical_dashes;
	vector<vector<char>> squares_claimed; // C=computer, U = user, <space> = unclaimed
	void recalculate_squares(Player player);
};

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

void Board::print() const
{
	static const char point = (char)254u;
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

void Board::add_move(int row, int col, bool orientation, Player player) // orientation1 = vertical, 0=horizontal
{
	if (orientation)
	{
		if (row < 0 || row >= size || col < 0 || col > size)
		{
			throw Invalid_Move{};
		}
		vertical_dashes[row][col] = 1;
	}
	else
	{
		if (row < 0 || row > size || col < 0 || col >= size)
		{
			throw Invalid_Move{};
		}
		horizontal_dashes[row][col] = 1;
	}
	recalculate_squares(player);
}

void Board::recalculate_squares(Player player)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (squares_claimed[i][j] == ' ' && horizontal_dashes[i][j] && horizontal_dashes[i + 1][j] && vertical_dashes[i][j] && vertical_dashes[i][j + 1])
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
	Board game{4};
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
	game.print();
}