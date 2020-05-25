#pragma once
#define AKANEENGINE_API __declspec(dllexport)
#include "../Engine/Transform.h"
#include "Shader.h"
#include "Texture2D.h"
#include "Material.h"
#include "../ECS/Component.h"
#include <string>

struct AKANEENGINE_API StaticMesh :Component
{
public:
	StaticMesh();

	GLuint vao;
	GLuint gIndirectBuffer;
	Transform transform;
	std::string material;
};

