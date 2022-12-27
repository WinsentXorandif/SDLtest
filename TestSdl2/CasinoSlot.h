#pragma once
#include "ObjectFactory.h"
#include "Timer.h"

enum GameState 
{
	Stopped,
	Running,
	Paused
};

const int MAX_BAR_TIMER = 50000;
const int LOOP_TIME = 5000;

class CasinoSlot
{
public:
	~CasinoSlot();

	void loadGameObjects(SDL_Renderer* renderer, TTF_Font* textFont);

	void startGame();

	void UpdateInput(bool& isRunning);

	void UpdateLoop();

	void renderGameObjects();

private:

	int timerSlot = 0;
	int numbelSlot = 0;
	int countedFrames = 0;

	GameState currState = Stopped;
	int CreditsInCounter = 0;
	int CreditsOutCounter = 0;
	int PlaysCounter = 0;

	ObjectFactory* objectFactory = nullptr;
	Timer* timer = nullptr;

};

