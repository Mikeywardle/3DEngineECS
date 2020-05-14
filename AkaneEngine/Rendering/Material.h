#pragma once

#define AKANEENGINE_API __declspec(dllexport)

#include <string>
#include <map>
#include "../ECS/Component.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Color.h"


struct AKANEENGINE_API Material : public Component
{
public:
	GLuint ID;
	Material(GLuint vertexShader, GLuint fragmentShader);

	void SetFloat(std::string name, float value);
	float GetFloat(std::string name);

	void SetVector3(std::string name, glm::vec3 value);
	glm::vec3 GetVector3(std::string name);

	void SetColor(std::string name, Color value);
	Color GetColor(std::string name);

	void SetMatrix4(const GLchar* name, const glm::mat4& matrix, GLboolean useShader);
	
private:

	std::map<std::string, float> floats;
	std::map<std::string, glm::vec3> vector3s;
	std::map<std::string, Color> colors;
	std::map<std::string, int>textureId;
	std::map<std::string, std::string>textures;

	void checkCompileErrors(GLuint object);
};

