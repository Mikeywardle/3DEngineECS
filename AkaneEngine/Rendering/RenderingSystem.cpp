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
		mesh.shader->Use();
		mesh.shader->SetMatrix4("projection", projection);
		mesh.shader->SetMatrix4("view", view);

		glActiveTexture(GL_TEXTURE0);
		mesh.texture->Bind();

		mesh.shader->SetVector4f("colour", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		mesh.shader->SetMatrix4("model", mesh.transform.GetModelMatrix());
		glBindVertexArray(mesh.vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}

StaticMesh* RenderingSystem::AddStaticMesh()
{
	staticMeshes.resize(1);
	return new(&staticMeshes[0]) StaticMesh();
}
