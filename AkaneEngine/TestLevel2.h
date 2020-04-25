#pragma once

#include "Engine/Level.h"
#include <iostream>

class TestLevel2 : public Level
{
public:
	TestLevel2()
	{
		cout << "Loading Level 2\n";
		levelObjects.push_back(new DebugActor());
	}
};
