#include "ApplicationContext.h"
#include <iostream>
#include "GameTime.h"

//TODO: Remove these!!!
#include "../TestLevel.h"
#include "ResourceManager.h"
#include "../Rendering/Camera.h"
#include "../Maths/Vector3.h"

using namespace std;

bool ApplicationContext::initialized;
bool ApplicationContext::running;
Game ApplicationContext::game;
InputModule ApplicationContext::inputModule;

GLFWwindow* ApplicationContext::window;

float ApplicationContext::contextHeight = 400.f;
float ApplicationContext::contextWidth = 600.f;

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void ApplicationContext::Initialize()
{
	initialized = true;
	//game.SwitchLevel<TestLevel>();
}

bool ApplicationContext::intialiseWindow()
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

	//if (fullscreen)
	//	window = glfwCreateWindow(contextWidth, contextHeight, applicationName, glfwGetPrimaryMonitor(), NULL);
	//else
		window = glfwCreateWindow(contextWidth, contextHeight , "Gravity Break", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}
	glEnable(GL_DEPTH_TEST);
	return true;
}

void ApplicationContext::GetFrameTime()
{
	float currentTime;
	currentTime = glfwGetTime();
	GameTime::frameTime = currentTime - GameTime::totalTime;	

	GameTime::deltaTime = GameTime::frameTime * GameTime::timeScale;
	GameTime::totalTime += GameTime::deltaTime;
	GameTime::totalRealTime += GameTime::frameTime;
}

int ApplicationContext::Run()
{
	if (!initialized) {
		cout << "ERROR : Game has not been initialized" << endl;
		return 1;
	}
	if (running) {
		cout << "Application is alreay running!!" << endl;
		return 1;
	}

	intialiseWindow();
	running = true;

	ResourceManager::LoadAssets();
	inputModule.SetWindow(window);
	   
	Camera camera = Camera();
	camera.transform.SetPositionRotation(glm::vec3(0, 0, 0), glm::quat(0, 0, 0, 0));

	StaticMesh* mesh = RenderingSystem::instance->AddStaticMesh();
	mesh->transform.SetPositionRotationScale(glm::vec3(4,-1,-1), glm::quat(0,0,90,0), glm::vec3(1, 1, 1));
	mesh->material = ResourceManager::GetMaterial("Test");
	mesh->mesh = ResourceManager::GetMesh("Mesh");

	StaticMesh* mesh2 = RenderingSystem::instance->AddStaticMesh();
	mesh2->transform.SetPositionRotationScale(glm::vec3(4, 1, -1), glm::quat(0, 0, 90, 0), glm::vec3(1, 1, 1));
	mesh2->material = ResourceManager::GetMaterial("Test2");
	mesh2->mesh = ResourceManager::GetMesh("Mesh");

	StaticMesh* mesh3;
	Material* mat = ResourceManager::GetMaterial("Gradient");
	Mesh* mes = mesh2->mesh = ResourceManager::GetMesh("Mesh");

	mesh3 = RenderingSystem::instance->AddStaticMesh();
	mesh3->transform.SetPositionRotationScale(glm::vec3(4, 1, 1), glm::quat(0, 0, 90, 0), glm::vec3(1, 1, 1));
	mesh3->material = mat;
	mesh3->mesh = mes;

	while (!glfwWindowShouldClose(window))
	{
		//cout <<"Frame:"<< 1.0f/GameTime::deltaTime << endl;
		inputModule.PollInputs();
		game.DoFrame(GameTime::deltaTime);
		game.DrawFrame();
		glfwSwapBuffers(window);
		GetFrameTime();
	}

	cout << "Exit" << endl;
	glfwTerminate();
	return 0;
}

void ApplicationContext::Exit()
{
	glfwSetWindowShouldClose(window, true);
}

Game* ApplicationContext::GetGame()
{
	return &game;
}
