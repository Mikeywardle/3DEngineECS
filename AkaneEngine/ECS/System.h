#pragma once
#define AKANEENGINE_API __declspec(dllexport)
#include "ComponentContext.h"

class AKANEENGINE_API System
{
public:
	virtual void Init() = 0;
	virtual void OnFrame(float deltaTime, ComponentContext* context) {};
};

