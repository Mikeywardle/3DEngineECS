#pragma once
#define AKANEENGINE_API __declspec(dllexport)
#include "../Engine/Transform.h"
#include "Material.h"
#include "Mesh.h"
#include <string>

struct AKANEENGINE_API StaticMesh
{
	Mesh* mesh;
	Material* material;
};

