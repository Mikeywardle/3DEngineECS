#define AKANEENGINE_API __declspec(dllexport)
#include <map>
#include <string>
#include <vector>
#include <glad/glad.h>

#include "../Rendering/Texture2D.h"
#include "../Rendering/Shader.h"
#include "../Rendering/Material.h"


class AKANEENGINE_API ResourceManager
{
public:
	static void LoadAssets();

	//Shaders
	static Shader* LoadShader(const GLchar* shaderFile, int shaderType, std::string name);
	static Shader* GetShader(std::string name);

	//Textures
	static Texture2D* LoadTexture(const GLchar* file, GLboolean alpaha, std::string name);
	static Texture2D* GetTexture(std::string name);

	//Materials
	static Material* LoadMaterial(const GLchar* file, std::string name);
	static Material* GetMaterial(std::string name);

	//Static Meshes

	//Skeletal Meshes

	//Audio

	static void Clear();

	static std::string resourcesPath;

private:
	ResourceManager() {}
	static Shader* loadShaderFromFile(const GLchar* shaderFile, int shaderType);
	static Texture2D* loadTextureFromFile(const char* file, GLboolean alpha);
	static Material* LoadMaterialFromFile(const char* file);

	static std::map<std::string, Shader*> shaderTable;
	static std::map<std::string, Texture2D*> textureTable;
	static std::map<std::string, Material*> materialTable;

	static void LoadTextures();
	static void LoadShaders();
	static void LoadMaterials();
};