#pragma once
#include <vector>
#include "System.h"
#include "Entity.h"
#include "ComponentContext.h"

class ECSManager
{
public:
	virtual void OnFrame(float deltaTime);
private:
	std::vector<System*> systems;
	ComponentContext componentContext;
};

