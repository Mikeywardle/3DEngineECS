#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include<stb_image.h>

std::map<std::string, Texture2D*> ResourceManager::textureTable;
std::map<std::string, Shader*> ResourceManager::shaderTable;
std::map<std::string, Material*> ResourceManager::materialTable;

std::string ResourceManager::resourcesPath = "resources";

void ResourceManager::LoadAssets()
{
	LoadTextures();
	LoadShaders();
	LoadMaterials();

	//LoadMeshes();
	//LoadAudio();
}

#pragma region Textures
void ResourceManager::LoadTextures()
{
	xml_document<>* textureSettings = XMLReader::parseXml(resourcesPath+"/Textures/_Textures.xml");
	xml_node<>* node = textureSettings->first_node();

	for (xml_node<>* textureNode = node->first_node(); textureNode; textureNode = textureNode->next_sibling())
	{
		std::string texturepath = resourcesPath + "/Textures/" + textureNode->first_node("file")->value();
		LoadTexture(texturepath.c_str(), GL_FALSE, textureNode->first_node("name")->value());
	}
	delete textureSettings;
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

Texture2D* ResourceManager::LoadTexture(const GLchar* file, GLboolean alpha, std::string name)
{
	textureTable[name] = loadTextureFromFile(file, alpha);
	return textureTable[name];
}

Texture2D* ResourceManager::GetTexture(std::string name)
{
	return textureTable[name];
}

#pragma endregion

#pragma region Shaders
void ResourceManager::LoadShaders()
{
	xml_document<>* shaderSettings = XMLReader::parseXml(resourcesPath + "/Shaders/_Shaders.xml");
	xml_node<>* node = shaderSettings->first_node();

	for (xml_node<>* shaderNode = node->first_node(); shaderNode; shaderNode = shaderNode->next_sibling())
	{
		std::string shaderpath = resourcesPath + "/Shaders/" + shaderNode->first_node("file")->value();
		//LoadShader(texturepath.c_str(), GL_FALSE, textureNode->first_node("name")->value());
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
	Shader* shader = new Shader;
	shader->Compile(shaderCode, shaderType);
	return shader;
}
#pragma endregion

#pragma region Materials
void ResourceManager::LoadMaterials()
{
	xml_document<>* materialSettings = XMLReader::parseXml(resourcesPath + "/Materials/_Materials.xml");
	xml_node<>* node = materialSettings->first_node();

	for (xml_node<>* materialNode = node->first_node(); materialNode; materialNode = materialNode->next_sibling())
	{
		std::string materialPath = resourcesPath + "/Textures/" + materialNode->first_node("file")->value();
		LoadMaterial(materialPath.c_str(), materialNode->first_node("name")->value());
	}
	delete materialSettings;

}

Material* ResourceManager::LoadMaterial(const GLchar* file, std::string name)
{
	materialTable[name] = LoadMaterialFromFile(file);
	return materialTable[name];
}

Material* ResourceManager::GetMaterial(std::string name)
{
	return materialTable[name];
}

Material* ResourceManager::LoadMaterialFromFile(const char* file)
{
	return nullptr;
}
#pragma endregion

void ResourceManager::Clear()
{
	for (auto iter : shaderTable)
		glDeleteProgram(iter.second->ID);

	for (auto iter : textureTable)
		glDeleteTextures(1, &iter.second->ID);
}
