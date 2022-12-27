#include "TextObject.h"
#include "TextureLoader.h"

TextObject::TextObject(std::string text, int x, int y, int width, int height, SDL_Color color, TTF_Font* font, SDL_Renderer* renderer)
{

	defaultText = text;
	gameRenderer = renderer;

	objTexture = TextureLoader::loadTTF(gameRenderer, defaultText + "0", color, font);

	xPos = x;
	yPos = y;
	objectWidth = width;
	objectHeight = height;
	textColor = color;
	textFont = font;

	destRect = { xPos, yPos, objectWidth, objectHeight };
}

void TextObject::Update()
{

}

void TextObject::Render(int index)
{
}


void TextObject::Render()
{
	SDL_RenderCopy(gameRenderer, objTexture, NULL, &destRect);
}

void TextObject::ChangeText(std::string newText)
{
	SDL_DestroyTexture(objTexture);
	objTexture = TextureLoader::loadTTF(gameRenderer, defaultText + newText, textColor, textFont);
}