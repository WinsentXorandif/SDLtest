#pragma once
#include <map>
#include <list>
#include <string>

#include "ImageObject.h"
#include "TextObject.h"
#include "AnimatedObject.h"
#include "Button.h"


using namespace std;

class ObjectFactory
{
public:

	ObjectFactory(SDL_Renderer* renderer, TTF_Font* textFont);

	void LoadObjects();

	void AnimateObjects(bool isToAnimate);

	bool UpdateMouse(bool& isRunning);

	void BlinkMouse();

	void RenderObjects(int num);

	void ChangeUIText(std::string newValue);

	void CleanObjects();

	int GetMAxSlot() {
		return imagesMap.size();
	}


private:

	bool IsAnimate = false;

	int index = 0;

	int maxSpriteClips = 0;

	TTF_Font* gameFont;

	SDL_Color textColor = { 0, 0, 0 };

	SDL_Renderer* gameRenderer;

	Button* button;

	GameObject* backGround;

	list<GameObject*> imagesList;
	map<int, list<GameObject*>> imagesMap;

	TextObject* TestFPS;
};

