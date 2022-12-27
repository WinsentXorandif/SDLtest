#pragma once
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

class TextureLoader
{
public:
	static SDL_Texture* LoadTexture(SDL_Renderer* renderer,const char* fileName);
	static SDL_Texture* loadTTF(SDL_Renderer* renderer,std::string text, SDL_Color textColor, TTF_Font* font);

};

