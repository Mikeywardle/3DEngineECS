#include "Shader.h"
#include <iostream>


Shader::Shader(const GLchar* shaderSource, int shaderType)
{
	// Vertex Shader
	ID = glCreateShader(shaderType);
	glShaderSource(ID, 1, &shaderSource, NULL);
	glCompileShader(ID);
	checkCompileErrors(ID);
}

void Shader::checkCompileErrors(GLuint object)
{
	GLint success;
	GLchar infoLog[1024];

	glGetShaderiv(object, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(object, 1024, NULL, infoLog);
		std::cout << "| ERROR::SHADER: Compile-time error:\n"
			<< infoLog << "\n -- --------------------------------------------------- -- "
			<< std::endl;
	}

}