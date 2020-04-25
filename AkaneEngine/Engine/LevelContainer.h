#pragma once

#define AKANEENGINE_API __declspec(dllexport)

#include <vector>

using namespace std;

class AKANEENGINE_API LevelContainer
{
public:
	LevelContainer();
	~LevelContainer();

	void AddObject(class Actor* actor);
	void StartPlay();

	static LevelContainer FromFile();

protected:
	vector<Actor*> levelObjects = vector<class Actor*>();
};

