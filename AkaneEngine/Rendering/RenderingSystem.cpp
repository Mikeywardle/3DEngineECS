#include "RenderingSystem.h"
#include "GLFW/glfw3.h"
#include "Camera.h"
#include "../Engine/ResourceManager.h"
#include "Material.h"
#include <string>
#include "StaticMesh.h"

void RenderingSystem::OnFrame(float deltaTime)
{
	glClearColor(0.2f, 0.1f, .35f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Camera* mainCamera = Camera::GetMainCamera();
	glm::mat4 projection = mainCamera->GetPerspective();
	glm::mat4 view = mainCamera->GetView();


	for (Entity entity : entities)
	{
		Transform& t = ecs.GetComponent<Transform>(entity);
		StaticMesh& s = ecs.GetComponent<StaticMesh>(entity);

		Material* material = s.material;
		Mesh* mesh = s.mesh;

		glUseProgram(material->ID);
		material->SetMatrix4("projection", projection);
		material->SetMatrix4("view", view);
		glBindVertexArray(mesh->VAO);
		unsigned int indices = mesh->indices.size();

		BindTextures(material);

		material->SetMatrix4("model", t.GetModelMatrix());
		glDrawElements(GL_TRIANGLES, indices, GL_UNSIGNED_INT, 0);
			
		
	}

	/*for (unsigned int i = 0; i< instanceCounts.size();i++)
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
			unsigned int indices = mesh->indices.size();

			BindTextures(material);

			for (int j = 0; j < instanceCounts[i]; j++) {

				material->SetMatrix4("model", staticMeshes[currentMesh].transform.GetModelMatrix());
				glDrawElements(GL_TRIANGLES, indices, GL_UNSIGNED_INT, 0);
				currentMesh++;
			}
		}
	}*/
}

void RenderingSystem::BindTextures(Material* material)
{
	for (int i = 0; i < material->textureIds.size(); i++) {
		glActiveTexture(GL_TEXTURE0+i);
		glBindTexture(GL_TEXTURE_2D, material->textureIds[i]);
	}
}
