#pragma once

#define AKANEENGINE_API __declspec(dllexport)

#include <string>
#include <map>
#include "../ECS/Component.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

struct AKANEENGINE_API Material : public Component
{
public:
	GLuint ID;
	Material(GLuint vertexShader, GLuint fragmentShader);

	std::map<std::string, float> floats;
	std::map<std::string, glm::vec2> vector2s;
	std::map<std::string, glm::vec3> vector3s;
	
private:

	std::map<std::string, int>textureId;
	std::map<std::string, std::string>textures;

	void checkCompileErrors(GLuint object);
};

