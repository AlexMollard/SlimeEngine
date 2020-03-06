#pragma once
#include "Material.h"
#include "TextureManager.h"

class MaterialManager
{
public:
	MaterialManager(TextureManager* textureManager);
	~MaterialManager();

	// Create / Add Functions
	//--------------------
	bool Create(std::string name, Texture* diffuse);
	bool Create(std::string name, Texture* diffuse, Texture* specular, Texture* normal, Texture* ambient, Texture* rough);
	void Create(std::string name, std::string diffuseName, std::string specularName, std::string normalName, std::string ambientName, std::string roughName);
	void Create(std::string name, std::string diffuseName, float diffuseStrength, std::string specularName, float specularStrength, std::string normalName, float normalStrength, std::string ambientName, float ambientStrength, std::string roughName, float roughStrength);
	bool Add(Material* newMaterial);

	// Get Functions
	//--------------------
	int GetIndex(std::string name);
	Material* Get(std::string name, bool creation = false);
	Material* Get(int index);

	// Light Functions
	//--------------------
	void SetDirLightDirection(glm::vec3 direction);

	// Misc Functions
	//--------------------
	bool DebugManager();
	void SetNames();
	std::vector<std::string> GetNames();
	Material* NotFound(bool creation, std::string name = "---", int index = 404);

protected:
	// Get a refrence to all textures
	TextureManager* textureManager = nullptr;
	
	// Keep track of all textures and names for future use
	std::vector<Material*> materialList;
	std::vector<std::string> materialNames;
};

