#pragma once
#define AKANEENGINE_API __declspec(dllexport)
#include "../Engine/Transform.h"
#include "Material.h"
#include "Mesh.h"
#include "../ECS/Component.h"
#include <string>

struct AKANEENGINE_API StaticMesh :Component
{
public:
	StaticMesh();

	Mesh* mesh;
	Material* material;
	Transform transform;

};

