#include "RenderingSystem.h"
#include "GLFW/glfw3.h"
#include "Camera.h"
#include "../Engine/ResourceManager.h"
#include "Material.h"

RenderingSystem* RenderingSystem::instance;

RenderingSystem::RenderingSystem()
{
	instance = this;
}

void RenderingSystem::OnFrame()
{
	glClearColor(0.2f, 0.1f, .35f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	Camera* mainCamera = Camera::GetMainCamera();
	glm::mat4 projection = mainCamera->GetPerspective();
	glm::mat4 view = mainCamera->GetView();

	for (StaticMesh mesh : staticMeshes) 
	{
		Material * material = ResourceManager::GetMaterial(mesh.material);

		glUseProgram(material->ID);
		material->SetMatrix4("projection", projection);
		material->SetMatrix4("view", view);
		material->SetMatrix4("model", mesh.transform.GetModelMatrix());

		BindTextures(material);

		glBindVertexArray(mesh.vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
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

void RenderingSystem::SetCameraMatrices()
{
}
