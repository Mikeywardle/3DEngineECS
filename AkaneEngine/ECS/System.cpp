#include "System.h"
#include "ECSManager.h"
#include "../Engine/ApplicationContext.h"
#include "../Engine/Game.h"

void System::OnRegister()
{
}

ECSManager& System::getECS()
{
	return ApplicationContext::GetGame()->ecs;
}
