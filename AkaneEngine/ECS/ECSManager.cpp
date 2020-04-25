#include "ECSManager.h"

void ECSManager::OnFrame(float deltaTime)
{
	for (System* system : systems)
	{
		system->OnFrame(deltaTime, &componentContext);
	}
}
