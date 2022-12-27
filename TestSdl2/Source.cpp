#include<iostream>
#include<SDL.h>
#include<SDL_image.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

const int width = 1024;
const int height = 800;


void DeInitSDL(int error)
{
	if (renderer != NULL) SDL_DestroyRenderer(renderer);
	if (window != NULL) SDL_DestroyWindow(window);
	IMG_Quit();
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

	int res;
	if ((res = IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) == 0)
	{
		printf("Init SDL_Image Error: %s", SDL_GetError());
		DeInitSDL(1);
	}
	if (res & IMG_INIT_PNG)printf("Initialized PNG library!\n");
	if (res & IMG_INIT_JPG)printf("Initialized JPG library!\n");

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

void mathCoordsToScreen(double x, double y, double scale, int centerX, int centerY, int& sx, int& sy)
{
	sx = round(centerX + x * scale);
	sy = round(centerY - y * scale);
}


int main(int argc, char* argv[])
{
	InitSDL();

	//----------------OLD Drawning Button setup
	SDL_Surface* surfaceButton = IMG_Load("Image/start33.png");
	if (surfaceButton == NULL)
	{
		printf("Could not load image! Error: %s", SDL_GetError());
		DeInitSDL(1);
	}
	//----------------OLD Drawning SpriteAll setup
	SDL_Surface* surfaceSpriteAll = IMG_Load("Image/spriteall.png");
	if (surfaceSpriteAll == NULL)
	{
		printf("Could not load image! Error: %s", SDL_GetError());
		DeInitSDL(1);
	}

	SDL_Surface* win_surf = SDL_GetWindowSurface(window);

	//----------------

	int basePoints = 3;
	bool Multy = true;
	bool IsRUN = true;
	//=========================
	int win_width = width;
	int win_height = height;

	SDL_Event sdlEvent;

	int mouse_x = win_width / 2;
	int mouse_y = win_height / 2;

	//=========================
	int x = 0, y = 0;
	int delta = 12;

	while (IsRUN)
	{
#pragma region INPUT
		while (SDL_PollEvent(&sdlEvent))
		{
			switch (sdlEvent.type)
			{
			case SDL_QUIT:
				IsRUN = false;
				break;
			case SDL_WINDOWEVENT:
				if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					win_width = sdlEvent.window.data1;
					win_height = sdlEvent.window.data2;
				}
				break;

			case SDL_MOUSEBUTTONDOWN:
				if (sdlEvent.button.button == SDL_BUTTON_LEFT)
				{
					mouse_x = sdlEvent.button.x;
					mouse_y = sdlEvent.button.y;
				}
				break;

			default: break;

			}
		}
#pragma endregion

#pragma region DRAWNING

		//---------------- OLD Drawning Button DRAWNING
		SDL_Rect scrRectButton = { 0, 0, 512, 512 };
		SDL_Rect dstRectButton = { 100, 100, 200, 200 };

		SDL_BlitSurface(surfaceButton, &scrRectButton, win_surf, NULL);//&dstRect);
		//---------------- OLD Drawning SpriteAll DRAWNING
		SDL_Rect scrRectSprite = { 0, y, 100, 100 };
		SDL_Rect dstRectSprite = { 300, 300, 400, 400 };

		y += delta;

		//printf("y = %d\n",y);

		if (y > 160) y = 0;

		//if (y > 600) delta = -2;
		//if (y < 0) delta = 2;

		SDL_BlitSurface(surfaceSpriteAll, &scrRectSprite, win_surf, &dstRectSprite);//&dstRect);

		SDL_UpdateWindowSurface(window);
		//----------------

		//================================= New Drawning Image
		//fsm, дерево поведения, боксинг анбоксинг. рут гар. коллект, , даб



		//=================================
#pragma endregion

		//SDL_RenderPresent(renderer);
		SDL_Delay(100);

	}

	SDL_FreeSurface(surfaceButton);
	SDL_FreeSurface(surfaceSpriteAll);
	DeInitSDL(0);
	return 0;

}

