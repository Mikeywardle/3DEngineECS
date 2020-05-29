#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include<stb_image.h>
#include <glm/vec3.hpp>
#include "../Utils/XMLReader.h"



std::map<std::string, Texture2D*> ResourceManager::textureTable;
std::map<std::string, Shader*> ResourceManager::shaderTable;
std::map<std::string, Material*> ResourceManager::materialTable;
std::map<std::string, Mesh*> ResourceManager::meshTable;

std::string ResourceManager::resourcesPath = "Resources";

void ResourceManager::LoadAssets()
{
	std::cout << "Loading Textures..."<< std::endl;
	LoadTextures();
	std::cout << "Loading Shaders..."<< std::endl;
	LoadShaders();
	std::cout << "Loading Materials..."<<std::endl;
	LoadMaterials();
	std::cout << "Loading Meshes..." << std::endl;
	LoadMeshes();
	//LoadAudio();
}

#pragma region Textures
void ResourceManager::LoadTextures()
{
	xml_document* textureSettings = XMLReader::parseXml(resourcesPath+"/Textures/_Textures.xml");

	for (xml_node textureNode = textureSettings->child("Textures").child("Texture"); textureNode; textureNode = textureNode.next_sibling())
	{
		std::string texturepath = resourcesPath + "/Textures/" + textureNode.child("file").first_child().value();
		std::string textureName = textureNode.child("name").first_child().value();

		//std::cout << "Loading " << textureName << " from" << texturepath << std::endl;

		LoadTexture(texturepath.c_str(), GL_FALSE, textureName);
	}
	delete textureSettings;
}

Texture2D* ResourceManager::LoadTexture(const GLchar* file, GLboolean alpha, std::string name)
{
	textureTable[name] = loadTextureFromFile(file, alpha);
	return textureTable[name];
}

Texture2D* ResourceManager::loadTextureFromFile(const char* file, GLboolean alpha)
{
	Texture2D* texture = new Texture2D();
	if (alpha)
	{
		texture->Internal_Format = GL_RGBA;
		texture->Image_Format = GL_RGBA;
	}

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* image = stbi_load(file, &width, &height, &nrChannels, 0);

	texture->Generate(width, height, image);

	stbi_image_free(image);
	return texture;
}

Texture2D* ResourceManager::GetTexture(std::string name)
{
	return textureTable[name];
}

#pragma endregion

#pragma region Shaders
void ResourceManager::LoadShaders()
{
	xml_document* shaderSettings = XMLReader::parseXml(resourcesPath + "/Shaders/_Shaders.xml");

	for (xml_node shaderNode = shaderSettings->child("Shaders").child("Shader"); shaderNode; shaderNode = shaderNode.next_sibling())
	{
		std::string shaderFilename = shaderNode.child("file").first_child().value();
		std::string shaderpath = resourcesPath + "/Shaders/" + shaderFilename;
		std::string shaderType =shaderNode.child("type").first_child().value();

		//std::cout << "Loading " << shaderNode.child("name").first_child().value() << " from" << shaderpath << std::endl;

		if(shaderType=="vertex")
			LoadShader(shaderpath.c_str(), GL_VERTEX_SHADER, shaderNode.child("name").first_child().value());
		else if (shaderType == "fragment")
			LoadShader(shaderpath.c_str(), GL_FRAGMENT_SHADER, shaderNode.child("name").first_child().value());
	}

	delete shaderSettings;
}

Shader* ResourceManager::LoadShader(const GLchar* shaderFile, int shaderType, std::string name)
{
	shaderTable[name] = loadShaderFromFile(shaderFile, shaderType);
	return shaderTable[name];
}

Shader* ResourceManager::GetShader(std::string name)
{
	return shaderTable[name];
}

Shader* ResourceManager::loadShaderFromFile(const GLchar* shaderFile, int shaderType)
{
	std::string shaderCodeString;
	try
	{
		// Open files
		std::ifstream vertexShaderFile(shaderFile);
		std::stringstream shaderStream;
		shaderStream << vertexShaderFile.rdbuf();
		vertexShaderFile.close();
		shaderCodeString = shaderStream.str();

	}
	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}
	const GLchar* shaderCode = shaderCodeString.c_str();
	Shader* shader = new Shader(shaderCode, shaderType);
	return shader;
}
#pragma endregion

#pragma region Materials
void ResourceManager::LoadMaterials()
{
	xml_document* materialSettings = XMLReader::parseXml(resourcesPath + "/Materials/_Materials.xml");

	for (xml_node materialNode = materialSettings->child("Materials").child("Material"); materialNode; materialNode = materialNode.next_sibling())
	{
		std::string materialPath = resourcesPath + "/Materials/" + materialNode.child("file").first_child().value();

		LoadMaterial(materialPath.c_str(), materialNode.child("name").first_child().value());
	}
	delete materialSettings;
}

Material* ResourceManager::LoadMaterial(const GLchar* file, std::string name)
{
	materialTable[name] = LoadMaterialFromFile(file);
	return materialTable[name];
}

Material* ResourceManager::LoadMaterialFromFile(const char* file)
{
	xml_document* materialValues = XMLReader::parseXml(file);

	xml_node valuesNode = materialValues->child("Material");

	std::string vertexShader = valuesNode.child("vertexShader").first_child().value();
	std::string fragmentShader = valuesNode.child("fragmentShader").first_child().value();

	Material* material = new Material(shaderTable[vertexShader]->ID, shaderTable[fragmentShader]->ID);

	std::string name;
	float r, g, b, a;

	for (xml_node colorNode = valuesNode.child("colors").child("color"); colorNode; colorNode = colorNode.next_sibling())
	{
		name = colorNode.child("name").first_child().value();
		r = atof(colorNode.child("r").first_child().value());
		g = atof(colorNode.child("g").first_child().value());
		b = atof(colorNode.child("b").first_child().value());
		a = atof(colorNode.child("a").first_child().value());

		Color color = Color(r, g, b, a);
		material->SetColor(name, color);
	}

	int id;
	for (xml_node textureNode = valuesNode.child("textures").child("texture"); textureNode; textureNode = textureNode.next_sibling())
	{
		name = textureNode.child("name").first_child().value();
		id =atoi(textureNode.child("id").first_child().value());

		material->SetTexture(textureTable[name]->ID, id);
	}
	delete materialValues;
	return material;
}

Material* ResourceManager::GetMaterial(std::string name)
{
	return materialTable[name];
}
#pragma endregion

#pragma region Meshes
Mesh* ResourceManager::GetMesh(std::string name)
{
	return meshTable[name];
}

void ResourceManager::LoadMeshes()
{
	xml_document* meshSettings = XMLReader::parseXml(resourcesPath + "/Meshes/_Meshes.xml");
	Assimp::Importer importer;

	for (xml_node meshNode = meshSettings->child("Meshes").child("Mesh"); meshNode; meshNode = meshNode.next_sibling())
	{
		std::string meshpath = resourcesPath + "/Meshes/" + meshNode.child("file").first_child().value();
		const aiScene* scene = importer.ReadFile(meshpath, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "Error Loading Model" << importer.GetErrorString() << std::endl;
		}
		else 
		{
			ProcessNode(scene->mRootNode, scene);
		}
	}
}

void ResourceManager::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		LoadMesh(mesh, scene);
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh* ResourceManager::LoadMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	//Loading Vertices (positions, normals, texture coordinates)
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;

		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;

		if (mesh->mTextureCoords[0])
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else
		{
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}

		vertices.push_back(vertex);
	}

	//Loading indices
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	std::string name(mesh->mName.C_Str());
	std::cout << name << std::endl;
	meshTable[name] = new Mesh(vertices, indices);
}

Mesh* ResourceManager::LoadMeshFromFile(const char* file)
{
	return new Mesh();
}
#pragma endregion

void ResourceManager::Clear()
{
	//for (auto iter : shaderTable)
	//	glDeleteProgram(iter.second->ID);

	//for (auto iter : textureTable)
	//	glDeleteTextures(1, &iter.second->ID);
}
