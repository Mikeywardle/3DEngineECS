#include "LevelContainer.h"
#include "Actor.h"
#include <iostream>

LevelContainer::LevelContainer()
{
}

LevelContainer::~LevelContainer()
{
	for (Actor* actor : levelObjects)
	{
		delete actor;
	}
}

void LevelContainer::AddObject(Actor* actor)
{
	levelObjects.push_back(actor);
	actor->OnStartPlay();
}

void LevelContainer::StartPlay()
{
	for (Actor* a : levelObjects) 
	{
		a->OnStartPlay();
	}
}

LevelContainer LevelContainer::FromFile()
{
	return LevelContainer();
}
