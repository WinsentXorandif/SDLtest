#pragma once
#include "GameObject.h"

class ImageObject : public GameObject
{
public:

	ImageObject(const char* fileName, int x, int y, int width, int height, SDL_Renderer* renderer);

	virtual void Update();

	virtual void Render();

	virtual void Render(int index);

};

