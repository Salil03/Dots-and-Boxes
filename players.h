#include "board.h"
using namespace std;

// Class for human player
class User
{
public:
	User(string nickname, Board *game) : nickname{nickname}, board{game}, initial{nickname[0]} {}; // constructor
	void make_move();																			   // add a move to the board from the user
	int score() { return (board->get_score(initial)); };										   // returns player's score after recalculating
	string nickname;																			   // nickname of player

private:
	char initial; // initial used for scoring. TODO: Check for clashes
	Board *board; // board attached to player
};

/*Prompts the user for a move and sends it to the attached board*/
void User::make_move()
{
	int row, col;
	bool vertical;
	cout << nickname << ", Make a move\n"
		 << "Enter row: ";
	cin >> row;
	cout << "Enter column: ";
	cin >> col;
	cout << "Enter orientation(1 = vertical, 0 = horizontal): ";
	cin >> vertical;
	board->add_move(row, col, vertical, initial);
}

// Class for computer player
class Computer
{
public:
	Computer(string nickname, string opponent_nickname, Board *game, int search_depth) : nickname{nickname}, board{game}, initial{nickname[0]}, opponent_initial{opponent_nickname[0]}, depth{search_depth} {}; // constructor
	int score() { return (board->get_score(initial)); };																																						// returns player's score
	class Invalid_Board																																															// error when computer can't make a move
	{
	};
	void make_move(); // add a move to the board from the computer
	string nickname;  // computer's nickname

private:
	char initial;																															// computer initial used for scoring
	char opponent_initial;																													// oponent's initial, used in evalutation function
	int depth;																																// depth for minimax														//
	Board *board;																															// attached board
	tuple<int, int, bool, int> minimax(Board &game, int depth, int alpha, int beta, bool maximize, char &max_agent, char &min_agent) const; // minimax solver with alpha-beta pruning
	int minimax_heuristic(Board &game, char &max_agent, char &min_agent) const;																// evaluation function
	vector<tuple<int, int, bool>> allowed_moves(Board &game) const;																			// returns a list of all the allowed moves in a position
	vector<pair<int, int>> get_neighbours(Board &game, const int &row, const int &col, const bool &vertical) const;							// returns list of squares which contain the given edge
	int filled_edges(Board &game, int &row, int &col) const;																				// returns the number of filled edges of a square
};

/*Calls appropriate solve() to compute next move and sends it to the attached board*/
void Computer::make_move()
{
	auto result = minimax(*(this->board), depth, -3000, 3000, true, initial, opponent_initial);
	// cout << get<0>(result) << " " << get<1>(result) << " " << get<2>(result) << " " << get<3>(result) << "\n";
	board->add_move(get<0>(result), get<1>(result), get<2>(result), initial);
}