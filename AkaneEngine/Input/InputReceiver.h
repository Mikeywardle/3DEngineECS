#pragma once
#include <string>
#include <vector>
#include "InputTypes.h"
#include "InputSubscription.h"
#include "InputModule.h"

#define AKANEENGINE_API __declspec(dllexport)

class AKANEENGINE_API InputReceiver
{
public:
	InputReceiver();
	~InputReceiver();

	void EnableInputs();
	void DisableInputs();

	template<typename Clazz, typename Function>
	void AddButtonMapping(std::string buttonName, ButtonEventType buttonEvenType, Clazz object, Function function){}

private:
	std::vector<InputSubscription> subscriptions = std::vector<InputSubscription>();
};


