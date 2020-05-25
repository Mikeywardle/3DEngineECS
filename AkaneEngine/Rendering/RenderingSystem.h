#pragma once

#define AKANEENGINE_API __declspec(dllexport)
#include "StaticMesh.h"
#include "glm/vec3.hpp"
#include <vector>

class AKANEENGINE_API RenderingSystem
{
public:
	RenderingSystem();

	void OnFrame();
	StaticMesh* AddStaticMesh();

	static RenderingSystem* instance;

private:
	std::vector<StaticMesh> staticMeshes;

	void BindTextures(Material* material);
	void SetCameraMatrices();
};

