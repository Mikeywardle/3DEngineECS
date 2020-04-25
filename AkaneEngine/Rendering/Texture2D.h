#pragma once

#define AKANEENGINE_API __declspec(dllexport)

#include <glad/glad.h>

class AKANEENGINE_API Texture2D
{
public:

	GLuint ID;
	GLuint Width, Height;

	GLuint Internal_Format;
	GLuint Image_Format;

	GLuint Wrap_S;
	GLuint Wrap_T;
	GLuint Filter_Min;
	GLuint Filter_Max;

	Texture2D();

	void Generate(GLuint width, GLuint height, unsigned char* data);
	void Bind() const;

};

