#include "players.h"
#include <random>

using namespace std;

auto rd = std::random_device{};
auto rng = std::default_random_engine{rd()}; // random engine for randomization

/*Solver which returns the next move calculated by Computer. It can directly access board's private members for better speed*/
tuple<int, int, bool> Computer::solve(Board &game) const
{
	// Generate random permutation of all edges
	vector<tuple<int, int, bool>> permutation(2 * (game.size + 1) * game.size);
	int k = 0;
	for (int vertical = 0; vertical <= 1; vertical++)
	{
		for (int i = 0; i < game.size + 1 - vertical; i++)
		{
			for (int j = 0; j < game.size + vertical; j++, k++)
			{
				permutation[k] = {i, j, vertical};
			}
		}
	}
	shuffle(permutation.begin(), permutation.end(), rng);

	/*iterate over each edge and check if it's allowed
	Edge is allowed if filling it doesn't add 3 edges to any square.
	*/
	for (const auto &[row, col, vertical] : permutation)
	{
		if ((vertical && game.vertical_dashes[row][col]) || (!vertical && game.horizontal_dashes[row][col]))
		{
			continue;
		}
		bool allowed = true;
		for (auto square : get_neighbours(game, row, col, vertical))
		{
			if (filled_edges(game, square.first, square.second) == 2)
			{
				allowed = false;
				break;
			}
		}
		if (allowed)
		{
			return {row, col, vertical};
		}
	}

	// If no edge is allowed, choose random edge which is not played before. TODO: add a algo here
	shuffle(permutation.begin(), permutation.end(), rng);
	for (const auto &[row, col, vertical] : permutation)
	{
		if ((vertical && !game.vertical_dashes[row][col]) || (!vertical && !game.horizontal_dashes[row][col]))
		{
			return {row, col, vertical};
		}
	}
	throw Invalid_Board{}; // no move can be played
}

/*Returns list of squares that contain edge with coordinate (row, col, vertical)*/
vector<pair<int, int>> Computer::get_neighbours(Board &game, int row, int col, bool vertical) const
{
	vector<pair<int, int>> neighbours;
	if (vertical)
	{
		if (col > 0)
		{
			neighbours.push_back({row, col - 1});
		}
		if (col < game.size)
		{
			neighbours.push_back({row, col});
		}
	}
	else
	{
		if (row > 0)
		{
			neighbours.push_back({row - 1, col});
		}
		if (row < game.size)
		{
			neighbours.push_back({row, col});
		}
	}
	return neighbours;
}

/*Returns number of filled_edges in square at position (row, col)*/
int Computer::filled_edges(Board &game, int row, int col) const
{
	int sum = 0;
	sum += game.horizontal_dashes[row][col];
	sum += game.vertical_dashes[row][col];
	sum += game.horizontal_dashes[row + 1][col];
	sum += game.vertical_dashes[row][col + 1];
	return sum;
}