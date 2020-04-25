#include "DebugActor.h"
#include <iostream>
#include "Game.h"
#include "ApplicationContext.h"
#include "../TestLevel2.h"

DebugActor::DebugActor()
{
	recieveFrameEvent = true;
	inputReceiver.AddButtonMapping("",ButtonEventType::PRESSED,this,&DebugActor::DebugButtonPress);
}

void DebugActor::OnStartPlay()
{
	Actor::OnStartPlay();
	std::cout << "Hello Debug Actor\n";
	
}

void DebugActor::DoDebugThing()
{
	std::cout << "Switching Scene\n";
	Game* game = ApplicationContext::GetGame();
	game->SwitchLevel<TestLevel2>();	
}

void DebugActor::DebugButtonPress()
{
	std::cout << "Button Pressed";
}

void DebugActor::OnFrame(float deltaTime)
{
	time += deltaTime;

	//std::cout << "Debug Actor\n";
	//if (time > 5.f)
	//{
	//	DoDebugThing();
	//	SetReceiveFrameEvent(false);
	//}
}
