#pragma once

#include "Engine/Level.h"
#include "Engine/DebugActor.h"

class TestLevel : public Level
{

public:
	TestLevel()
	{
		levelObjects.push_back(new DebugActor());
	}
};
