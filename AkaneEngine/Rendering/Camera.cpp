#include "Camera.h"
#include <glm//gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Engine/ApplicationContext.h"
#include <iostream>

Camera* Camera::mainCamera;

Camera::Camera()
{
	if (mainCamera == nullptr)
		SetMainCamera(this);
}

void Camera::SetMainCamera(Camera* camera)
{
	mainCamera = camera;
}

Camera* Camera::GetMainCamera()
{
	return mainCamera;
}

glm::mat4 Camera::GetView() 
{
	return glm::lookAt(transform.GetPosition(), transform.GetPosition() + transform.GetForward(), transform.GetUp());
}

glm::mat4 Camera::GetPerspective() {
	return glm::perspective(glm::radians(fov), ApplicationContext::contextWidth / ApplicationContext::contextHeight, nearPlane, farPlane);
}
