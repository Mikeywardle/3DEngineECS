#pragma once

#define AKANEENGINE_API __declspec(dllexport)

#include "Event.h"
#include <map>
#include <string>
#include "Level.h"
#include "../ECS/ECSManager.h"

class AKANEENGINE_API Game
{
public:

	Game();

	Event<float>* GetFrameEvent();
	Event<float>* GetEndFrameEvent();

	ECSManager ecs;

	void DoFrame(float deltaTime);
	void DoEndFrame(float deltaTime);

	void LoadLevel(std::string levelName);
	void UnloadLevel(std::string levelName);

	template<class Clazz>
	void SwitchLevel() 
	{
		if (activeLevel != nullptr)
			delete activeLevel;

		activeLevel = new Clazz();
		activeLevel->StartPlay();
	}

	class Actor* CreateObject();
	void DestroyObject(class Actor* toDestroy);

private:

	Event<float> Frame;
	Event<float> EndFrame;

	map<std::string ,Level*> loadedLevels =  map<std::string,Level*>();
	Level* activeLevel;
};

