#include "CasinoSlot.h"

CasinoSlot::~CasinoSlot()
{
	objectFactory->CleanObjects();

	delete objectFactory;

	delete timer;
}

void CasinoSlot::loadGameObjects(SDL_Renderer* renderer, TTF_Font* textFont)
{
	objectFactory = new ObjectFactory(renderer, textFont);

	timer = new Timer();

	objectFactory->LoadObjects();
}

void CasinoSlot::startGame()
{
	CreditsInCounter = 10;

	switch (currState)
	{
	case Stopped:

		if (CreditsInCounter > 0)
		{
			currState = Running;
			//CreditsInCounter--;
			objectFactory->AnimateObjects(true);

			timer->start();
		}

		break;

	case Running:

		currState = Paused;

		objectFactory->AnimateObjects(false);

		timer->pause();

		break;

	case Paused:

		currState = Running;

		objectFactory->AnimateObjects(true);

		timer->unpause();

		break;

	default:
		break;
	}


}

void CasinoSlot::UpdateInput(bool& isRunning)
{
	if (objectFactory->UpdateMouse(isRunning))
	{
		startGame();
	}
}


void CasinoSlot::UpdateLoop()
{

	if (timer->getTicks() > LOOP_TIME)
	{
		printf("Passed the 5 seconds");

		numbelSlot = 0;

		currState = Stopped;

		PlaysCounter++;

		objectFactory->AnimateObjects(false);

		timer->stop();
	}


	timerSlot += timer->getTicks();

	if (timerSlot >= MAX_BAR_TIMER)
	{
		if (numbelSlot < objectFactory->GetMAxSlot())
		{
			numbelSlot++;
		}
		timerSlot = 0;
	}

	Uint32 avgFPS = countedFrames / (timer->getTicks() / 1000.f);
	if (avgFPS > 2000000)
	{
		avgFPS = 0;
	}

	objectFactory->ChangeUIText(to_string(avgFPS));

	objectFactory->BlinkMouse();

	countedFrames++;
}

void CasinoSlot::renderGameObjects()
{
	objectFactory->RenderObjects(numbelSlot);
}
