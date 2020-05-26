#include "RenderingSystem.h"
#include "GLFW/glfw3.h"
#include "Camera.h"
#include "../Engine/ResourceManager.h"
#include "Material.h"
#include <string>
#include <algorithm>

RenderingSystem* RenderingSystem::instance;

RenderingSystem::RenderingSystem()
{
	instance = this;
}

bool meshSort(StaticMesh a, StaticMesh b)
{
	return a.material > b.material && a.mesh > b.mesh;
}

void RenderingSystem::OnFrame()
{
	glClearColor(0.2f, 0.1f, .35f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Camera* mainCamera = Camera::GetMainCamera();
	glm::mat4 projection = mainCamera->GetPerspective();
	glm::mat4 view = mainCamera->GetView();

	//Sort Meshes to be in order
	std::sort(staticMeshes.begin(), staticMeshes.end(), meshSort);

	std::vector<int> instanceCounts;
	Material* currentMaterial;
	Material* nextMaterial;
	int currentcount = 0;

	currentMaterial = staticMeshes[0].material;

	//first Pass to get number of obejcts per instance
	for (StaticMesh staticMesh : staticMeshes)
	{
		nextMaterial = staticMesh.material;

		if (nextMaterial == currentMaterial) {
			currentcount++;
		}
		else 
		{
			instanceCounts.push_back(currentcount);
			currentcount = 1;
			currentMaterial = nextMaterial;
		}
	}

	instanceCounts.push_back(currentcount);
	int currentMesh = 0;

	for (unsigned int i = 0; i< instanceCounts.size();i++)
	{
		Material * material  = staticMeshes[currentMesh].material;
		Mesh* mesh = staticMeshes[currentMesh].mesh;

		if (mesh == NULL)
		{
			currentMesh += instanceCounts[i];
		}
		else 
		{

			glUseProgram(material->ID);
			material->SetMatrix4("projection", projection);
			material->SetMatrix4("view", view);
			glBindVertexArray(staticMeshes[currentMesh].mesh->VAO);

			BindTextures(material);

			for (int j = 0; j < instanceCounts[i]; j++) {

				material->SetMatrix4("model", staticMeshes[currentMesh].transform.GetModelMatrix());
				glDrawArrays(GL_TRIANGLES, 0, 6);
				currentMesh++;
			}
		}
	}
}

StaticMesh* RenderingSystem::AddStaticMesh()
{
	staticMeshes.resize(staticMeshes.size()+1);
	return new(&staticMeshes[staticMeshes.size()-1]) StaticMesh();
}

void RenderingSystem::BindTextures(Material* material)
{
	for (int i = 0; i < material->textureIds.size(); i++) {
		glActiveTexture(GL_TEXTURE0+i);
		glBindTexture(GL_TEXTURE_2D, material->textureIds[i]);
	}
}
