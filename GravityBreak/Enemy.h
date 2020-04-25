#pragma once
#include "Engine/Actor.h"
#include "Input/InputReceiver.h"

class Enemy: public Actor
{
public:
	Enemy();
	~Enemy();
	void OnStartPlay() override;

protected:
	void OnFrame(float deltaTime) override;
	InputReceiver* inputReceiver;
};

