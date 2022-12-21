#include<iostream>
#include<SDL.h>
#include<SDL_image.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

const int width = 800;
const int height = 600;


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
	if ((res = IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG )) == 0)
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

void mathCoordsToScreen(double x, double y, double scale, int centerX, int centerY, int &sx, int &sy) 
{
	sx = round(centerX + x * scale);
	sy = round(centerY - y * scale);
}

int main(int argc, char* argv[])
{
	InitSDL();
	//----------------
	SDL_Surface* surface = IMG_Load("Image/Start02.png");
	if (surface == NULL) 
	{
		printf("Could not load image! Error: %s", SDL_GetError());
		DeInitSDL(1);
	}

	SDL_Surface* win_surf = SDL_GetWindowSurface(window);



	//----------------
	SDL_SetRenderDrawColor(renderer, 128, 128, 0, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 128, 0, 128, 255);
	SDL_RenderDrawLine(renderer, 0, 100, width, 100);

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
	while (IsRUN)
	{

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


        #pragma region DRAWNING
		SDL_SetRenderDrawColor(renderer, 128, 128, 0, 255);
		SDL_RenderClear(renderer);

		int countPoints = basePoints;
		SDL_Point* points = (SDL_Point*)malloc(sizeof(SDL_Point) * (countPoints + 1));

		float alfa = 0;
		for (int i = 0; i < countPoints; i++)
		{
			alfa += 2 * M_PI / countPoints;
			mathCoordsToScreen(200 * cos(alfa), 200 * sin(alfa), 1.0,
				//win_width / 2, win_height / 2,
				mouse_x, mouse_y,
				points[i].x, points[i].y);
		}

		points[countPoints] = points[0];
		SDL_SetRenderDrawColor(renderer, 100, 50, 0, 255);
		SDL_RenderDrawLines(renderer, points, countPoints + 1);

		free(points);

		if (Multy)
		{
			basePoints++;
		}
		else
		{
			basePoints--;
		}

		if (Multy && basePoints > 100 || !Multy && basePoints <= 3)
		{
			Multy = !Multy;
		}
        #pragma endregion

		//----------------
		SDL_Rect scrRect = { 0, 0, 512, 512 };
		SDL_Rect dstRect = { 100, 100, 200, 200 };

		SDL_BlitSurface(surface, &scrRect, win_surf, NULL);//&dstRect);
		SDL_UpdateWindowSurface(window);
		//----------------

	    //SDL_RenderPresent(renderer);
	    SDL_Delay(100);

    }

	SDL_FreeSurface(surface);

	DeInitSDL(0);
	return 0;

}