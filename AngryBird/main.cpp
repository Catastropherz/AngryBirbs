#include "Game.h"

int main()
{
	Game* AngryBirdsGame = new Game();
	AngryBirdsGame->PlayGame();
	delete AngryBirdsGame;

    return 0;
}