#pragma once
#include "GameObject.h"
#include <string>

class TextObject : public virtual GameObject
{
public:
	TextObject(std::string text, int x, int y, int width, int height,SDL_Color color, TTF_Font* font,SDL_Renderer* renderer);

	virtual void Update();

	virtual void Render();

	virtual void Render(int index);

	void ChangeText(std::string newText);

private:
	SDL_Color textColor = {0,0,0};
	std::string defaultText = "";

	TTF_Font* textFont;
};

