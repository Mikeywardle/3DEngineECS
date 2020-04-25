#pragma once
#define AKANEENGINE_API __declspec(dllexport)

class AKANEENGINE_API GameTime
{
public:
	static float deltaTime;
	static float totalTime;
	static float totalRealTime;
	static float timeScale;
	static float frameTime;

private:
	GameTime() {};
};

