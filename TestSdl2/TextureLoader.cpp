#include "TextureLoader.h"

SDL_Texture* TextureLoader::LoadTexture(SDL_Renderer* renderer, const char* filename)
{
	SDL_Surface* tempSurface = IMG_Load(filename);

	if (tempSurface == NULL)
	{
		printf("Error creating surface with file: %s: Error: %s \n", filename, SDL_GetError());
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);

	SDL_FreeSurface(tempSurface);

	return texture;

}

SDL_Texture* TextureLoader::loadTTF(SDL_Renderer* renderer, std::string text, SDL_Color textColor, TTF_Font* font)
{
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);

	SDL_Texture* gTextTexture = nullptr;

	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		gTextTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

		if (gTextTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		SDL_FreeSurface(textSurface);
	}

	return gTextTexture;
}
