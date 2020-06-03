#pragma once

#define AKANEENGINE_API __declspec(dllexport)
#include <vector>
#include "Material.h"
#include "../ECS/System.h"

class AKANEENGINE_API RenderingSystem : public System
{
public:
	virtual void OnFrame(float deltTaime) override;
private:
	void BindTextures(Material* material);
};

