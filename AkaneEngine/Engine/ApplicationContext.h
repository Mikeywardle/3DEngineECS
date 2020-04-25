#pragma once

#define AKANEENGINE_API __declspec(dllexport)

#include "Game.h"
#include "../Input/InputModule.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class AKANEENGINE_API ApplicationContext
{
public:
	static void Initialize();
	static int Run();
	static void Exit();
	static Game* GetGame();

	static float contextHeight;
	static float contextWidth;


private:
	ApplicationContext() {}

	static bool initialized;
	static bool running;
	static GLFWwindow* window;

	static Game game;
	static InputModule inputModule;

	static bool intialiseWindow();
	static void GetFrameTime();
};

