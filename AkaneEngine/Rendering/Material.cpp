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

void Material::SetFloat(std::string name, float value)
{
	floats[name] = value;
	glUniform1f(glGetUniformLocation(ID, name.c_str), value);
}

float Material::GetFloat(std::string name)
{
	return floats[name];
}

void Material::SetVector3(std::string name, glm::vec3 value)
{
	vector3s[name] = value;
	glUniform3f(glGetUniformLocation(ID, name.c_str), value.x, value.y, value.z);
}

glm::vec3 Material::GetVector3(std::string name)
{
	return vector3s[name];
}

void Material::SetColor(std::string name, Color value)
{
	colors[name] = value;
	glUniform4f(glGetUniformLocation(ID, name.c_str), value.r, value.g, value.b, value.a);
}

void Material::SetMatrix4(const GLchar* name, const glm::mat4& matrix, GLboolean useShader)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

Color Material::GetColor(std::string name)
{
	return colors[name];
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
