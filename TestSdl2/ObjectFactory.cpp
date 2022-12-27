#include "ObjectFactory.h"
#include <typeinfo>


ObjectFactory::ObjectFactory(SDL_Renderer* renderer, TTF_Font* font)
{
	gameFont = font;
	gameRenderer = renderer;
}

void ObjectFactory::LoadObjects()
{
	TestFPS = new TextObject("GameFPS: ", 10, 10, 200, 50, textColor, gameFont, gameRenderer);

	maxSpriteClips = 14;
	const char* fileNameSprites = "Resources/Images/spriteall3.png";

	imagesList.clear();
	imagesList.push_back(new AnimatedObject(fileNameSprites, 240, 200, 100, 100, 14, 14, gameRenderer));
	imagesList.push_back(new AnimatedObject(fileNameSprites, 240, 310, 100, 100, 14, 14, gameRenderer));
	imagesList.push_back(new AnimatedObject(fileNameSprites, 240, 420, 100, 100, 14, 14, gameRenderer));

	imagesMap.insert({ 0, imagesList });

	imagesList.clear();
	imagesList.push_back(new AnimatedObject(fileNameSprites, 350, 200, 100, 100, 14, 14, gameRenderer));
	imagesList.push_back(new AnimatedObject(fileNameSprites, 350, 310, 100, 100, 14, 14, gameRenderer));
	imagesList.push_back(new AnimatedObject(fileNameSprites, 350, 420, 100, 100, 14, 14, gameRenderer));

	imagesMap.insert({ 1, imagesList });

	imagesList.clear();
	imagesList.push_back(new AnimatedObject(fileNameSprites, 460, 200, 100, 100, 14, 14, gameRenderer));
	imagesList.push_back(new AnimatedObject(fileNameSprites, 460, 310, 100, 100, 14, 14, gameRenderer));
	imagesList.push_back(new AnimatedObject(fileNameSprites, 460, 420, 100, 100, 14, 14, gameRenderer));

	imagesMap.insert({ 2, imagesList });

	imagesList.clear();
	imagesList.push_back(new AnimatedObject(fileNameSprites, 570, 200, 100, 100, 14, 14, gameRenderer));
	imagesList.push_back(new AnimatedObject(fileNameSprites, 570, 310, 100, 100, 14, 14, gameRenderer));
	imagesList.push_back(new AnimatedObject(fileNameSprites, 570, 420, 100, 100, 14, 14, gameRenderer));

	imagesMap.insert({ 3, imagesList });

	imagesList.clear();
	imagesList.push_back(new AnimatedObject(fileNameSprites, 680, 200, 100, 100, 14, 14, gameRenderer));
	imagesList.push_back(new AnimatedObject(fileNameSprites, 680, 310, 100, 100, 14, 14, gameRenderer));
	imagesList.push_back(new AnimatedObject(fileNameSprites, 680, 420, 100, 100, 14, 14, gameRenderer));

	imagesMap.insert({ 4, imagesList });

	backGround = new ImageObject("Resources/Images/greenflowers.png", 0, 0, 1024, 768, gameRenderer);
	button = new Button("Resources/Images/start33.png", 650, 580, 256, 115, gameRenderer);
}

void ObjectFactory::AnimateObjects(bool isAnimate)
{
	IsAnimate = isAnimate;

	printf("AnimateObjects(bool isAnimate) isAnimate = %d\n", isAnimate);

	for (int i = 0; i < imagesMap.size(); i++)
	{

		for (auto const& image : imagesMap[i])
		{
			AnimatedObject* animatedObj = dynamic_cast<AnimatedObject*>(image);
			if (animatedObj != nullptr)
			{

				animatedObj->Animate(isAnimate);
			}
		}
	}
}


bool ObjectFactory::UpdateMouse(bool& isRunning)
{
	return button->Handle_events(isRunning);
}


void ObjectFactory::BlinkMouse()
{
	button->Update();
}



void ObjectFactory::ChangeUIText(std::string stringValue)
{
	TestFPS->ChangeText(stringValue);
}

void ObjectFactory::RenderObjects(int num)
{
	backGround->Render();
	TestFPS->Render();

	for (int i = 0; i < imagesMap.size(); i++)
	{
		for (auto const& image : imagesMap[i])
		{
			image->Render();
		}
	}
	//if (IsAnimate) {
	for (int i = 0; i < num; i++)
	{
		for (auto const& image : imagesMap[i])
		{
			image->Render(index);
			index++;
			index = index >= maxSpriteClips ? 0 : index;
		}
	}
	//}

	button->Render();
}

void ObjectFactory::CleanObjects()
{
	for (auto const& image : imagesList)
	{
		delete image;
	}

	delete TestFPS;
	delete backGround;
	delete button;

	imagesMap.clear();

}