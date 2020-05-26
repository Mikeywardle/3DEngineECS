#pragma once
#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>


struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Mesh
{
	Mesh();
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	void Initialize();
	GLuint VAO, VBO, EBO;

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
};

