#include "System.h"
#include "ECSManager.h"
#include "../Engine/ApplicationContext.h"
#include "../Engine/Game.h"

ECSManager System::getECS()
{
	return ApplicationContext::GetGame()->ecs;
}
