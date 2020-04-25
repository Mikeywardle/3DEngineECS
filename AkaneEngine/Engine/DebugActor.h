#pragma once

#define AKANEENGINE_API __declspec(dllexport)

#include "Actor.h"
#include "../Input/InputReceiver.h"
class AKANEENGINE_API DebugActor : public Actor
{
public:
	DebugActor();
	virtual void OnStartPlay() override;

private:
	float time = 0;
	InputReceiver inputReceiver = InputReceiver();

	void DoDebugThing();
	void DebugButtonPress();

protected:
	virtual void OnFrame(float deltaTime)override;
};

