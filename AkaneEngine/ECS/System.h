#pragma once

#define AKANEENGINE_API __declspec(dllexport)
#include <vector>
#include "ECSDefinitions.h"

class AKANEENGINE_API System {
public:
	std::vector<Entity> entities;
	virtual void OnRegister();
	virtual void OnFrame(float deltaTime) {};
	class ECSManager& getECS();

protected:
	//ECSManager* ecs;

};
