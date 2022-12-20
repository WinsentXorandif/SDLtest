#include<iostream>
#include<SDL.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

const int width = 800;
const int height = 600;


void DeInitSDL(int error)
{
	if (renderer != NULL) SDL_DestroyRenderer(renderer);
	if (window != NULL) SDL_DestroyWindow(window);
	SDL_Quit();
	exit(error);

}

void InitSDL() 
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Init SDL Error: %s", SDL_GetError());
		DeInitSDL(1);
	}

	window = SDL_CreateWindow("Test SDL Window", 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED,
		width, height, 
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (window == NULL)
	{
		printf("Create Window Error: %s", SDL_GetError());
		DeInitSDL(1);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		printf("Create Renderer Error: %s", SDL_GetError());
		DeInitSDL(1);
	}
}


int main(int argc, char* argv[])
{
	InitSDL();

	SDL_SetRenderDrawColor(renderer, 128, 128, 0, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 128, 0, 128, 255);
	SDL_RenderDrawLine(renderer, 0, 100, width, 100);


	SDL_RenderPresent(renderer);

	SDL_Delay(10000);

	DeInitSDL(0);
	return 0;

}