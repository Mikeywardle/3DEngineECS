#pragma once

#define AKANEENGINE_API __declspec(dllexport)

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


class AKANEENGINE_API Shader {

public:

	GLuint ID;
	Shader() {};
	Shader(const GLchar* shaderSource, int shaderType);

private:
	void checkCompileErrors(GLuint object);
};

