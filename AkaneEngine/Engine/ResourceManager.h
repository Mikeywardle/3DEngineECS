#define AKANEENGINE_API __declspec(dllexport)
#include <map>
#include <string>
#include <glad/glad.h>

#include "../Rendering/Texture2D.h"
#include "../Rendering/Shader.h"
#include "../Utils/XMLReader.h"

class AKANEENGINE_API ResourceManager
{
public:
	static Shader shaders[];
	static Texture2D textures[]; 

	static void LoadAssets();

	//Shaders
	static Shader* LoadShader(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile, std::string name);
	static Shader* GetShader(std::string name);

	//Textures
	static Texture2D* LoadTexture(const GLchar* file, GLboolean alpaha, std::string name);
	static Texture2D* GetTexture(std::string name);

	//Materials

	//Static Meshes

	//Skeletal Meshes

	//Audio

	static void Clear();

	static std::string resourcesPath;

private:
	ResourceManager() {}
	static Shader* loadShaderFromFile(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFIle = nullptr);
	static Texture2D* loadTextureFromFile(const char* file, GLboolean alpha);

	static std::map<std::string, Shader*> shaderTable;
	static std::map<std::string, Texture2D*> textureTable;

	static void LoadTextures();
	static void LoadShaders();
};