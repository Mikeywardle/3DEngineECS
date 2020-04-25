#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include<stb_image.h>

std::map<std::string, Texture2D*> ResourceManager::textureTable;
std::map<std::string, Shader*> ResourceManager::shaderTable;

std::string ResourceManager::resourcesPath = "resources";

void ResourceManager::LoadAssets()
{
	LoadTextures();
	LoadShaders();

	//LoadMaterials();
	//LoadMeshes();
	//LoadAudio();
}

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

Shader* ResourceManager::LoadShader(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile, std::string name)
{
	shaderTable[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
	return shaderTable[name];
}

Shader* ResourceManager::GetShader(std::string name)
{
	return shaderTable[name];
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

void ResourceManager::Clear()
{
	for (auto iter : shaderTable)
		glDeleteProgram(iter.second->ID);

	for (auto iter : textureTable)
		glDeleteTextures(1, &iter.second->ID);
}

Shader* ResourceManager::loadShaderFromFile(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	try
	{
		// Open files
		std::ifstream vertexShaderFile(vShaderFile);
		std::ifstream fragmentShaderFile(fShaderFile);
		std::stringstream vShaderStream, fShaderStream;
		// Read file's buffer contents into streams
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();
		// close file handlers
		vertexShaderFile.close();
		fragmentShaderFile.close();
		// Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		// If geometry shader path is present, also load a geometry shader
		if (gShaderFile != nullptr)
		{
			std::ifstream geometryShaderFile(gShaderFile);
			std::stringstream gShaderStream;
			gShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	}
	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();
	const GLchar* gShaderCode = geometryCode.c_str();
	// 2. Now create shader object from source code
	Shader* shader = new Shader;
	shader->Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
	return shader;
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


