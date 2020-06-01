#include "ECS/System.h"
#include "ECS/ECSManager.h"
#include "X.h"
#include <iostream>

struct BComponent {
	int id;
};

extern ECSManager manager;

class BSystem : public System
{
public:
	virtual void OnFrame(float deltaTime) override
	{
		for (Entity entity : entities)
		{
			XComponent x = manager.GetComponent<XComponent>(entity);
			BComponent a = manager.GetComponent<BComponent>(entity);

			std::cout << a.id << ";" << x.id << std::endl;
		}
	}
};