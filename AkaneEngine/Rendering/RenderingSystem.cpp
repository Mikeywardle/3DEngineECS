#include "RenderingSystem.h"
#include "GLFW/glfw3.h"
#include "Camera.h"

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
		mesh.shader->SetMatrix4("projection", projection);
		mesh.shader->SetMatrix4("view", view);

		glUseProgram(mesh.materialID);
		mesh.shader->SetMatrix4("model", mesh.transform.GetModelMatrix());

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, ID);

		glBindVertexArray(mesh.vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}

StaticMesh* RenderingSystem::AddStaticMesh()
{
	staticMeshes.resize(staticMeshes.size+1);
	return new(&staticMeshes[staticMeshes.size-1]) StaticMesh();
}
