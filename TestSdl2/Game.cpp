#include "Game.h"


Game::Game()
{
	casinoSlot = new CasinoSlot();
}

Game::~Game()
{
	delete casinoSlot;
}

void Game::init(const char* title, int xPosition, int yPosition, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		printf("Subsystem has been initialised!\n");

		gWindow = SDL_CreateWindow(title, xPosition, yPosition, width, height, flags);

		if (gWindow)
		{
			printf("Game Window created\n");
		}
		else
		{
			printf("Error creating window: Error: %s\n", SDL_GetError());
			isRunning = false;
			return;
		}

		renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

			printf("Renderer has been created!\n");
		}
		else
		{
			printf("Error creating renderer. Error %s\n", SDL_GetError());
			isRunning = false;
			return;
		}
		isRunning = true;
	}

	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		isRunning = false;
		return;
	}

	loadAssets();
}

void Game::loadAssets()
{
	gameFont = TTF_OpenFont("Resources/Fonts/editundo.ttf", 50);
	casinoSlot->loadGameObjects(renderer, gameFont);
	printf("Assets are loaded!\n");
}

void Game::handleEvents()
{
	casinoSlot->UpdateInput(isRunning);
}

void Game::update()
{
	casinoSlot->UpdateLoop();
}

void Game::render()
{
	SDL_RenderClear(renderer);

	casinoSlot->renderGameObjects();

	SDL_RenderPresent(renderer);
}

void Game::limitFrameRate(bool isFrameStart)
{
	if (isFrameStart)
	{
		frameStart = SDL_GetTicks();
	}
	else
	{
		frameDeltaTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameDeltaTime)
		{
			SDL_Delay(frameDelay - frameDeltaTime);
		}
	}
}

void Game::clean()
{
	SDL_DestroyWindow(gWindow);

	SDL_DestroyRenderer(renderer);

	TTF_CloseFont(gameFont);

	SDL_Quit();

	TTF_Quit();

	gWindow = nullptr;

	renderer = nullptr;

	printf("The game has been cleaned!");
}

