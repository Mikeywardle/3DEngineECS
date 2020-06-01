#include "ApplicationContext.h"
#include <iostream>
#include "GameTime.h"

//TODO: Remove these!!!
#include "../TestLevel.h"
#include "ResourceManager.h"
#include "../Rendering/Camera.h"
#include "../Rendering/StaticMesh.h"
#include "../Rendering/RenderingSystem.h"

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

	//game.SwitchLevel<TestLevel>();

	   
	Camera camera = Camera();
	camera.transform.SetPositionRotation(glm::vec3(0, 0, 0), glm::quat(0, 0, 0, 0));

	ECSManager& ecs = game.ecs;

	ecs.RegisterComponent<StaticMesh>();
	ecs.RegisterComponent<Transform>();

	RenderingSystem* rs = ecs.RegisterSystem<RenderingSystem>();

	Signature signature;
	signature.set(ecs.GetComponentType<Transform>());
	signature.set(ecs.GetComponentType<StaticMesh>());
	ecs.SetSystemSignature<RenderingSystem>(signature);

	game.GetFrameEvent()->AddListener(rs, &RenderingSystem::OnFrame);

	Entity mesh = ecs.CreateEntity();
	ecs.AddComponent(mesh, StaticMesh());
	ecs.AddComponent(mesh, Transform());

	ecs.GetComponent<Transform>(mesh).SetPositionRotationScale(glm::vec3(8,-1,-1), glm::quat(0,90,0,0), glm::vec3(1, 1, 1));
	ecs.GetComponent<StaticMesh>(mesh).material = ResourceManager::GetMaterial("Test");
	ecs.GetComponent<StaticMesh>(mesh).mesh = ResourceManager::GetMesh("Cube.001");

	Entity mesh2 = ecs.CreateEntity();
	ecs.AddComponent(mesh2, StaticMesh());
	ecs.AddComponent(mesh2, Transform());

	ecs.GetComponent<Transform>(mesh2).SetPositionRotationScale(glm::vec3(8, 1, -1), glm::quat(0, 90, 0, 0), glm::vec3(1, 1, 1));
	ecs.GetComponent<StaticMesh>(mesh2).material = ResourceManager::GetMaterial("Test2");
	ecs.GetComponent<StaticMesh>(mesh2).mesh = ResourceManager::GetMesh("Cube");

	Entity mesh3 = ecs.CreateEntity();
	ecs.AddComponent(mesh3, StaticMesh());
	ecs.AddComponent(mesh3, Transform());

	ecs.GetComponent<Transform>(mesh3).SetPositionRotationScale(glm::vec3(8, 1, 1), glm::quat(0, 90, 0, 0), glm::vec3(1, 1, 1));
	ecs.GetComponent<StaticMesh>(mesh3).material = ResourceManager::GetMaterial("Gradient");
	ecs.GetComponent<StaticMesh>(mesh3).mesh = ResourceManager::GetMesh("Cube");


	while (!glfwWindowShouldClose(window))
	{
		//cout <<"Frame:"<< 1.0f/GameTime::deltaTime << endl;
		inputModule.PollInputs();
		game.DoFrame(GameTime::deltaTime);
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
