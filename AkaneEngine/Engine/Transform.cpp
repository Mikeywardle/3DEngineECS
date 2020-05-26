#include "Transform.h"

glm::vec3 Transform::WorldForward = glm::vec3(0, 0, 1);
glm::vec3 Transform::WorldRight= glm::vec3(1, 0, 0);
glm::vec3 Transform::WorldUp = glm::vec3(0, 1, 0);

#pragma region Getters
Transform::Transform()
{
	CalculateModel();
}

glm::mat4 Transform::GetModelMatrix()
{
	return model;
}

glm::vec3 Transform::GetPosition()
{
	return position;
}

glm::quat Transform::GetRotation()
{
	return rotation;
}

glm::vec3 Transform::GetScale()
{
	return scale;
}

glm::vec3 Transform::GetForward()
{
	glm::vec3 forward;
	forward.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.z));
	forward.y = sin(glm::radians(rotation.z));
	forward.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.z));
	return forward = glm::normalize(forward);
}

glm::vec3 Transform::GetRight()
{
	return glm::normalize(glm::cross(GetForward(), WorldUp));;
}

glm::vec3 Transform::GetUp()
{
	return glm::normalize(glm::cross(GetRight(), GetForward()));
}
#pragma endregion

#pragma region Setters
void Transform::SetPosition(glm::vec3 newPosition)
{
	position = newPosition;
	CalculateModel();
}

void Transform::SetPositionRotation(glm::vec3 newPosition, glm::quat newRotation)
{
	position = newPosition;
	rotation = newRotation;
	CalculateModel();
}

void Transform::SetPositionRotationScale(glm::vec3 newPosition, glm::quat newRotation, glm::vec3 newScale)
{
	position = newPosition;
	rotation = newRotation;
	scale = newScale;
	CalculateModel();
}

void Transform::CalculateModel()
{
	model = glm::mat4(1.0f);
	model = translate(model, position);
	model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, scale);
}
#pragma endregion
