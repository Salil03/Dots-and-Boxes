#include "algo.h"
using namespace std;

void game_loop(Board &game, Computer &user, Computer &computer) // void game_loop(Board &game, User &user, Computer &computer)
{
	bool user_turn = true;
	int previous_score = 0;
	game.print();
	while (!game.finished())
	{
		if (user_turn)
		{
			previous_score = user.score();
			user.make_move();
			user_turn = previous_score < user.score();
		}
		else
		{
			previous_score = computer.score();
			computer.make_move();
			user_turn = previous_score >= computer.score();
		}
		game.print();
		cout << user.nickname << ": " << user.score() << "\n";
		cout << computer.nickname << ": " << computer.score() << "\n";
	}
	cout << "GAME ENDS\n Winner is " << (user.score() >= computer.score() ? user.nickname : computer.nickname) << "\n";
}

int main()
{
	Board game{3};
	Computer salil{"Salil", &game}; // User salil{"Salil", &game};
	Computer cosmos{"Cosmos", &game};
	game_loop(game, salil, cosmos);
}