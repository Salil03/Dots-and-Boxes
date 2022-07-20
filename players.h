#include "board.h"
using namespace std;

// Class for human player
class User
{
public:
	User(string nickname, Board *game) : nickname{nickname}, squares{0}, board{game}, initial{nickname[0]} {}; // constructor
	void make_move();																						   // add a move to the board from the user
	int score() { return (squares = board->get_score(initial)); };											   // returns player's score after recalculating
	string nickname;																						   // nickname of player

private:
	char initial; // initial used for scoring. TODO: Check for clashes
	int squares;  // number of squares owned by player
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
	board->add_move(row, col, vertical, Player::user, initial);
}

// Class for computer player
class Computer
{
public:
	Computer(string nickname, Board *game) : nickname{nickname}, squares{0}, board{game}, initial{nickname[0]} {}; // constructor
	int score() { return (squares = board->get_score(initial)); };												   // returns player's score
	class Invalid_Board																							   // error when computer can't make a move
	{
	};
	void make_move(); // add a move to the board from the computer
	string nickname;  // computer's nickname

private:
	char initial;																			   // initial used for scoring. TODO: Check for clashes
	int squares;																			   // squares owned by computer
	Board *board;																			   // attached board
	tuple<int, int, bool> solve(Board &game) const;											   // function to calculate next move
	vector<pair<int, int>> get_neighbours(Board &game, int row, int col, bool vertical) const; // returns list of squares which contain the given edge
	int filled_edges(Board &game, int row, int col) const;									   // returns the number of filled edges of a square
};

/*Calls solve() to compute next move and sends it to the attached board*/
void Computer::make_move()
{
	tuple<int, int, bool> result = solve(*(this->board));
	board->add_move(get<0>(result), get<1>(result), get<2>(result), Player::computer, initial);
}