#include "Game.h"

#undef main
int main()
{
	srand(time(NULL));

	//Create the Game
	Game game;

	//Initialize the game
	game.InitGame();

	//Runs the game until it returns :)
	return game.Run();
}