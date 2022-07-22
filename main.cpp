#include "algo.h"
using namespace std;

void game_loop(Board &game, User &user, Computer &computer, bool first_move)
{
	bool user_turn = first_move;
	int previous_score = 0;
	if (first_move)
	{
		cout << user.nickname << " VS " << computer.nickname << ", Game Begins!\n\n";
	}
	else
	{
		cout << computer.nickname << " VS " << user.nickname << ", Game Begins!\n\n";
	}
	while (!game.finished())
	{
		if (user_turn)
		{
			game.print();
			previous_score = user.score();
			user.make_move();
			user_turn = previous_score < user.score();
		}
		else
		{
			game.print();
			previous_score = computer.score();
			cout << "Thinking.....\n";
			computer.make_move();
			user_turn = previous_score >= computer.score();
		}
		cout << user.nickname << ": " << user.score() << "\n";
		cout << computer.nickname << ": " << computer.score() << "\n";
	}
	game.print();
	cout << "GAME ENDS\n Winner is " << (user.score() >= computer.score() ? user.nickname : computer.nickname) << "\n";
}

int main()
{
	Board game{3};
	string user_name;
	cout << "Enter your name: ";
	cin >> user_name;
	user_name[0] = toupper(user_name[0]);
	User user{user_name, &game};
	int search_depth = 8;
	bool first_move;
	cout << "Want first move?(0/1): ";
	cin >> first_move;
	if (user_name[0] != 'C')
	{
		Computer cosmos("Cosmos", user_name, &game, search_depth);
		game_loop(game, user, cosmos, first_move);
	}
	else
	{
		Computer HAL("HAL 9000", user_name, &game, search_depth);
		game_loop(game, user, HAL, first_move);
	}
}