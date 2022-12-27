#include "ImageObject.h"
#include "TextureLoader.h"

ImageObject::ImageObject(const char* fileName, int x, int y, int width, int height, SDL_Renderer* renderer)
{
	gameRenderer = renderer;

	objTexture = TextureLoader::LoadTexture(gameRenderer, fileName);

	xPos = x;
	yPos = y;
	objectWidth = width;
	objectHeight = height;

	srcRect = { 0,0,0,0 };
	destRect = { xPos,yPos,objectWidth,objectHeight };

}

void ImageObject::Update()
{

}

void ImageObject::Render(int index)
{
}


void ImageObject::Render()
{

	SDL_RenderCopy(gameRenderer, objTexture, NULL, &destRect);
}