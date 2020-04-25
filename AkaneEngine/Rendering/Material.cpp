#include "Material.h"
#include <iostream>

Material::Material(GLuint vertexShader, GLuint fragmentShader)
{
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	glLinkProgram(ID);
	checkCompileErrors(ID);
}

void Material::checkCompileErrors(GLuint object)
{
	GLint success;
	GLchar infoLog[1024];

	glGetShaderiv(object, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(object, 1024, NULL, infoLog);
		std::cout << "| ERROR::SHADER: Compile-time error: \n"
			<< infoLog << "\n -- --------------------------------------------------- -- "
			<< std::endl;
	}
}
