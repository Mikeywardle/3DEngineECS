#include "ECS/System.h"
#include "ECS/ECSManager.h"
#include "X.h"
#include <iostream>

struct AComponent
{
	int id;
};

extern ECSManager manager;

class ASystem : public System
{

public:
	virtual void OnFrame(float deltaTime) override
	{
		for (Entity entity : entities)
		{
			XComponent x = manager.GetComponent<XComponent>(entity);
			AComponent a = manager.GetComponent<AComponent>(entity);

			std::cout << a.id << ";" << x.id << std::endl;
		}
	}

};