#pragma once
#define AKANEENGINE_API __declspec(dllexport)

#include <map>
#include "Component.h"
#include "EcsTypeDefs.h"

struct AKANEENGINE_API Entity
{
	EntityID ID;
//	std::map<, Component*> components;
};

