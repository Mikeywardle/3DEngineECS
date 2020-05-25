#pragma once
#define AKANEENGINE_API __declspec(dllexport)

#include "EcsTypeDefs.h"

struct AKANEENGINE_API Component
{
	EntityID entityID;
};

