#pragma once
#include <SDL.h>
//#include <SDL_image.h>
//#include <SDL_ttf.h>
#include <stdio.h>
#include "ObjectFactory.h"
#include "CasinoSlot.h"


class Game
{
public:
	Game();

	~Game();

	void init(const char* title,int xPosition, int yPosition,int width, int height, bool fullscreen);

	void loadAssets();

	void handleEvents();

	void update();

	void render();

	void clean();

	void limitFrameRate(bool isFrameStart);

	bool running() { return isRunning; };

private:

	bool isRunning = false;
	SDL_Window* gWindow = nullptr;
	CasinoSlot* casinoSlot = nullptr;
	TTF_Font* gameFont = nullptr;
	SDL_Renderer* renderer = nullptr;
	
#pragma region Variables for the FPS limit
	
	const int FPS = 80;

	const int frameDelay = 1000 / FPS;

	Uint32 frameStart = 0;

	float frameDeltaTime = 0;
	
#pragma endregion Variables for the FPS limit

};

