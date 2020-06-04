#include "RenderingSystem.h"
#include "Camera.h"
#include "../Engine/ResourceManager.h"
#include "Material.h"
#include "StaticMesh.h"
#include "../ECS/ECSManager.h"
#include <set>

struct RenderSortingData
{
public:
	RenderSortingData(Mesh* mesh, Material* material, Entity entity)
	{
		this->mesh = mesh;
		this->material = material;
		entities.push_back(entity);
	}

	Mesh* mesh;
	Material* material;
	std::vector<Entity> entities;
};

void RenderingSystem::OnFrame(float deltaTime)
{
	ECSManager& ecs = getECS();

	glClearColor(0.2f, 0.1f, .35f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Camera* mainCamera = Camera::GetMainCamera();
	glm::mat4 projection = mainCamera->GetPerspective();
	glm::mat4 view = mainCamera->GetView();

	std::vector<RenderSortingData> data;

	bool entityMatched;
	for (Entity entity : entities)
	{
		entityMatched = false;
		StaticMesh& s = ecs.GetComponent<StaticMesh>(entity);

		 for (RenderSortingData rsd : data)
		 {
			 if (rsd.mesh == s.mesh && rsd.material == s.material)
			 {
				 rsd.entities.push_back(entity);
				 entityMatched = true;
				 break;
			 }
		 }

		 if (!entityMatched) 
			 data.push_back(RenderSortingData(s.mesh, s.material, entity));
	}


	for (RenderSortingData rsd : data)
	{
		Material* material = rsd.material;
		Mesh* mesh = rsd.mesh;

		glUseProgram(material->ID);
		material->SetMatrix4("projection", projection);
		material->SetMatrix4("view", view);
		BindTextures(material);

		glBindVertexArray(mesh->VAO);
		unsigned int indices = mesh->indices.size();

		for (Entity entity : rsd.entities)
		{
			Transform& t = ecs.GetComponent<Transform>(entity);

			material->SetMatrix4("model", t.GetModelMatrix());
			glDrawElements(GL_TRIANGLES, indices, GL_UNSIGNED_INT, 0);

		}

	}
}

void RenderingSystem::BindTextures(Material* material)
{
	for (int i = 0; i < material->textureIds.size(); i++) {
		glActiveTexture(GL_TEXTURE0+i);
		glBindTexture(GL_TEXTURE_2D, material->textureIds[i]);
	}
}
