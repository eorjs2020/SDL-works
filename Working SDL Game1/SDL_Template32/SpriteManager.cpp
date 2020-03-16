#include "SpriteManager.h"
#include "Sprite.h"

SpriteManager::SpriteManager()
{
}

SpriteManager::~SpriteManager()
{
}

void SpriteManager::cleanup()
{
	for (int i = 0; i < sprites.size(); i++)
	{
		sprites[i]->cleanup();
		delete sprites[i];
	}
}

void SpriteManager::updateAll(float deltaTime)
{
	for (int i = 0; i < sprites.size(); i++)
	{
		sprites[i]->update(deltaTime);
	}
}

void SpriteManager::drawAll()
{
	for (int i = 0; i < sprites.size(); i++)
	{
		sprites[i]->draw();
	}
}
