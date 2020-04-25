#include "InputModule.h"
#include <iostream>

void OnKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	std::cout << key << ";" << scancode << ";" << action << ";" << mods << "\n";
}

void OnMouseButtonPressed(GLFWwindow* window, int button, int action, int mods)
{
	std::cout << button << ";" << action << ";" << mods << "\n";
}

InputModule::InputModule()
{

}

void InputModule::SetWindow(GLFWwindow* window)
{
	this->window = window;

	glfwSetKeyCallback(window, OnKeyPressed);
	glfwSetMouseButtonCallback(window,OnMouseButtonPressed);
}

void InputModule::PollInputs()
{
	glfwPollEvents();
}



