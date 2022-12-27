#include "AnimatedObject.h"
#include "TextureLoader.h"
#include <stdlib.h>

AnimatedObject::AnimatedObject(const char* fileName, int x, int y, int width, int height, int SpriteClips, int ssRows, SDL_Renderer* renderer)
{

	gameRenderer = renderer;
	objTexture = TextureLoader::LoadTexture(gameRenderer, fileName);

	xPos = x;
	yPos = y;
	objectWidth = width;
	objectHeight = height;

	destRect = { xPos,yPos,objectWidth,objectHeight };

	maxSpriteClips = SpriteClips;
	spriteSheetRowsCount = ssRows;

	loadSpriteSheet(objTexture);
}

void AnimatedObject::Update()
{

}

void AnimatedObject::Render(int index)
{
	indexPic = index;
	currClip = &gSpriteClips[index];
	SDL_RenderCopy(gameRenderer, objTexture, currClip, &destRect);
}


void AnimatedObject::Render()
{
	currClip = &gSpriteClips[indexPic];// [frame / maxSpriteClips] ;
	SDL_RenderCopy(gameRenderer, objTexture, currClip, &destRect);

	/*
	if(isAnimated)
	{
		frame++;
		if (frame / maxSpriteClips >= maxSpriteClips)
		{
			frame = 0;
		}
	}
	*/
}

void AnimatedObject::loadSpriteSheet(SDL_Texture* texture)
{
	if (texture == nullptr)
	{
		printf("Invalid Texture!");
		return;
	}

	for (size_t i = 0; i < maxSpriteClips; i++)
	{
		gSpriteClips.push_back({});
	}

	int nextFrameWidth = 0;
	int nextFrameHeight = 0;
	int spriteRow = 0;

	for (int i = 0; i < maxSpriteClips; i++)
	{
		gSpriteClips[i].x = nextFrameWidth;
		gSpriteClips[i].y = nextFrameHeight;
		gSpriteClips[i].w = objectWidth;
		gSpriteClips[i].h = objectHeight;

		nextFrameWidth += objectWidth;

		spriteRow++;

		if (spriteRow >= spriteSheetRowsCount)
		{
			nextFrameWidth = 0;
			nextFrameHeight += objectHeight;
			spriteRow = 0;
		}
	}
}