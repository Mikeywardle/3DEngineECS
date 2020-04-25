#pragma once
#define AKANEENGINE_API __declspec(dllexport)
#include "../Engine/Transform.h"
#include "Shader.h"
#include "Texture2D.h"

struct AKANEENGINE_API StaticMesh
{
public:
	StaticMesh();

	GLuint vao;
	GLuint gIndirectBuffer;

	Transform transform;
	Shader* shader;
	Texture2D* texture;
};

