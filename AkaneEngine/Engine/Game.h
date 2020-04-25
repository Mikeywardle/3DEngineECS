#pragma once

#define AKANEENGINE_API __declspec(dllexport)

#include "Event.h"
#include <map>
#include <string>
#include "Level.h"
#include "../Rendering/RenderingSystem.h"

using namespace std;

class AKANEENGINE_API Game
{
public:

	Event<float>* GetFrameEvent();
	Event<float>* GetEndFrameEvent();

	void DoFrame(float deltaTime);
	void DoEndFrame(float deltaTime);

	void LoadLevel(string levelName);
	void UnloadLevel(string levelName);

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

	void DrawFrame();

private:

	Event<float> Frame;
	Event<float> EndFrame;

	map<string ,Level*> loadedLevels =  map<string,Level*>();
	Level* activeLevel;

	RenderingSystem renderingSystem = RenderingSystem();
};

