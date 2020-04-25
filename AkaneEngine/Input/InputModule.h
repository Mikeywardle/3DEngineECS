#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <map>
#include "../Engine/Event.h"

#define AKANEENGINE_API __declspec(dllexport)

class AKANEENGINE_API InputModule
{
public:
	InputModule();
	void SetWindow(GLFWwindow* window);
	void PollInputs();

private:
	GLFWwindow* window;
	//std::map<,Event<>> ButtonBindings;

};

