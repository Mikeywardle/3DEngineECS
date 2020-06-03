#pragma once

#define AKANEENGINE_API __declspec(dllexport)
#include <set>
#include "ECSDefinitions.h"

class AKANEENGINE_API System {
public:
	std::set<Entity> entities;
	virtual void OnFrame(float deltaTime) {};
	class ECSManager getECS();

};
