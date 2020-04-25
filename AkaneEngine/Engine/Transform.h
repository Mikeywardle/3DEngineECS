#pragma once
#define AKANEENGINE_API __declspec(dllexport)

#include "glm/vec3.hpp"
#include <glm/gtc/quaternion.hpp> 
#include <glm/gtx/quaternion.hpp>

struct AKANEENGINE_API Transform
{
public:

	Transform();
	static glm::vec3 WorldForward;
	static glm::vec3 WorldRight;
	static glm::vec3 WorldUp;

	glm::mat4 GetModelMatrix();
	glm::vec3 GetPosition();
	glm::quat GetRotation();
	glm::vec3 GetScale();

	glm::vec3 GetForward();
	glm::vec3 GetRight();
	glm::vec3 GetUp();

	void SetPosition(glm::vec3 newPosition);
	void SetPositionRotation(glm::vec3 newPosition, glm::quat newRotation);
	void SetPositionRotationScale(glm::vec3 newPosition, glm::quat newRotation, glm::vec3 newScale);

private:
	glm::vec3 position = glm::vec3(0,0,0);
	glm::quat rotation = glm::quat(0,0,0,0);
	glm::vec3 scale = glm::vec3(1,1,1);

	glm::vec3 forward = WorldForward;
	glm::vec3 right = WorldRight;
	glm::vec3 up = WorldUp;

	glm::mat4 model;

	void CalculateModel();
	void CalculateVectors();
};
