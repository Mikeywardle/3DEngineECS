#pragma once
#define AKANEENGINE_API __declspec(dllexport)
#include "../Engine/Transform.h"
#include "Shader.h"
#include "Texture2D.h"
#include "Material.h"
#include "../ECS/Component.h"

struct AKANEENGINE_API StaticMesh :Component
{
public:
	StaticMesh();

	GLuint vao;
	GLuint gIndirectBuffer;
	GLuint materialID;

	Transform transform;
};

