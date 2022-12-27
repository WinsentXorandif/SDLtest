#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class  GameObject
{

public:

	virtual void Update() = 0;

	virtual void Render() = 0;

	virtual void Render(int index) = 0;

protected:

	int xPos = 0;
	int yPos = 0;

	int objectWidth = 0;
	int objectHeight = 0;
	SDL_Texture* objTexture = nullptr;
	SDL_Renderer* gameRenderer = nullptr;
	SDL_Rect srcRect, destRect;
};

