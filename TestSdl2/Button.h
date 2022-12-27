#pragma once
#include "GameObject.h"
#include <vector>

const int MAX_CLIPS = 2;
const float MAX_TIMER = 1.0f;

class Button :
	public GameObject
{
public:

	Button(const char* fileName, int x, int y, int width, int height, SDL_Renderer* renderer);

	virtual void Update();
	virtual void Render();
	virtual void Render(int index);

	bool Handle_events(bool& isRunning);


private:
	int index = 0;

	float timer = 0;
	float newTime = 0;
	float dt = 0;
	float lastTime = 0;
	void loadSpriteSheet(SDL_Texture* texture);
	SDL_Rect* currClip = nullptr;
	std::vector<SDL_Rect> buttonClips;

};

