#pragma once

#define AKANEENGINE_API __declspec(dllexport)

#include "Event.h"
#include <string>

using namespace std;

 class AKANEENGINE_API Actor
{
public:

	Actor();
	~Actor();
	
	string name = "newActor";
	bool recieveFrameEvent=false;
	bool recieveEndFrameEvent= false;

	void SetReceiveFrameEvent(bool canRecieveFrameEvent);
	void SetReceiveEndFrameEvent(bool canRecieveEndFrameEvent);

	virtual void OnStartPlay();

protected:

	virtual void OnFrame(float deltaTime);
	virtual void OnEndFrame(float deltaTime);

	EventDelegate<float>* frameDelegate;
	EventDelegate<float>* endFrameDelegate;
};