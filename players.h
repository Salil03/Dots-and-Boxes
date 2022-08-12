#include "board.h"
using namespace std;

// Class for human player
class User
{
public:
	User(string name, Board *game) : nickname{name}, initial{name[0]}, board{game} {}; // constructor
	void make_move();																   // add a move to the board from the user
	int score() { return (board->get_score(initial)); };							   // returns player's score after recalculating
	string nickname;																   // nickname of player

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
	try
	{
		board->add_move(row, col, vertical, initial);
	}
	catch(...)
	{
		cout << "Invalid move, please make a valid move" << endl;
		make_move();
	}
}

// Class for computer player
class Computer
{
public:
	Computer(string name, string opponent_nickname, Board *game, int search_depth) : nickname{name}, initial{name[0]}, opponent_initial{opponent_nickname[0]}, minimax_depth{search_depth}, board{game} {}; // constructor
	int score() { return (board->get_score(initial)); };																																					// returns player's score
	class Invalid_Board																																														// error when computer can't make a move
	{
	};
	void make_move(); // add a move to the board from the computer
	string nickname;  // computer's nickname

private:
	char initial;																																			 // computer initial used for scoring
	char opponent_initial;																																	 // oponent's initial, used in evalutation function
	int minimax_depth;																																		 // depth for minimax
	vector<tuple<int, int, bool, int>> move_stack;																											 // pending moves to be played
	Board *board;																																			 // attached board
	void chain_solver(Board game, int depth);																												 // minimax with chain analysis
	void dfs(Board &game, int node_row, int node_col, int parent_row, int parent_col, vector<tuple<int, int, bool>> &moves, int &start_row, int &start_col); // dfs to search for chains
	tuple<int, int, bool, int> minimax(Board &game, int depth, int alpha, int beta, bool maximize, char &max_agent, char &min_agent) const;					 // minimax solver with alpha-beta pruning
	int minimax_heuristic(Board &game, char &max_agent, char &min_agent) const;																				 // evaluation function
	vector<tuple<int, int, bool>> allowed_moves(Board &game) const;																							 // returns a list of all the allowed moves in a position
	vector<pair<int, int>> get_neighbours(Board &game, const int &row, const int &col, const bool &vertical) const;											 // returns list of squares which contain the given edge
	int filled_edges(Board &game, const int &row, const int &col) const;																					 // returns the number of filled edges of a square
};

/*Calls appropriate solve() to compute next move and sends it to the attached board*/
void Computer::make_move()
{
	if (move_stack.empty())
	{
		chain_solver(*board, minimax_depth);
	}
	tuple<int, int, bool, int> result = move_stack[0];
	move_stack.erase(move_stack.begin());
	// cout << get<0>(result) << " " << get<1>(result) << " " << get<2>(result) << " " << get<3>(result) << "\n";
	board->add_move(get<0>(result), get<1>(result), get<2>(result), initial);
}