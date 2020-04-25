#pragma once
#define AKANEENGINE_API __declspec(dllexport)
#include "../Engine/Transform.h"

struct AKANEENGINE_API Camera
{
public:
	Camera();

	Transform transform;

	float fov = 45.f;

	float nearPlane = 0.1f;
	float farPlane = 20.f;

	glm::mat4 GetPerspective();
	glm::mat4 GetView();

	static void SetMainCamera(Camera* camera);
	static Camera* GetMainCamera();

private:
	static Camera* mainCamera;
};

