#include "Game.h"

int main()
{
	Game* AngryBirdsGame = new Game(1280,720);
	AngryBirdsGame->PlayGame();
	delete AngryBirdsGame;

    return 0;
}