#include "Actor.h"
#include <iostream>
#include "Game.h"
#include "ApplicationContext.h"

Actor::Actor()
{
}

Actor::~Actor()
{
	SetReceiveFrameEvent(false);
	SetReceiveEndFrameEvent(false);
}

void Actor::SetReceiveFrameEvent(bool canRecieveFrameEvent)
{
	Game* game = ApplicationContext::GetGame();

	if(canRecieveFrameEvent)
	{ 
		frameDelegate = game->GetFrameEvent()->AddListener(this, &Actor::OnFrame);
	} else {
		game->GetFrameEvent()->RemoveListener(frameDelegate);
	}

	recieveFrameEvent = canRecieveFrameEvent;
}

void Actor::SetReceiveEndFrameEvent(bool canRecieveEndFrameEvent)
{
	Game* game = ApplicationContext::GetGame();

	if (canRecieveEndFrameEvent)
	{
		endFrameDelegate = game->GetEndFrameEvent()->AddListener(this, &Actor::OnEndFrame);
	} else {
		game->GetFrameEvent()->RemoveListener(endFrameDelegate);
	}

	recieveEndFrameEvent = canRecieveEndFrameEvent;
}

void Actor::OnStartPlay()
{
	SetReceiveFrameEvent(recieveFrameEvent);
	SetReceiveEndFrameEvent(recieveEndFrameEvent);
}

void Actor::OnFrame(float deltaTime)
{
}

void Actor::OnEndFrame(float deltaTime)
{
}
