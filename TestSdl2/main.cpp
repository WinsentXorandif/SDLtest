#include "Game.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;


int main(int argc, char* args[])
{
	Game* game = new Game();
	game->init("Slot New Test",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		false);

	while (game->running())
	{
		game->limitFrameRate(true);

		game->handleEvents();

		game->update();

		game->render();

		game->limitFrameRate(false);
	}

	game->clean();
	delete game;
	return 0;
}


