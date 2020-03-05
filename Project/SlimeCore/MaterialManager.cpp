#include "MaterialManager.h"
#include <iostream>

MaterialManager::MaterialManager(TextureManager* textureManager)
{
	this->textureManager = textureManager;
	Create("None",nullptr);
}

MaterialManager::~MaterialManager()
{
	for (int i = 0; i < materialList.size(); i++)
	{
		if (materialList[i] != nullptr)
		{
			delete materialList[i];
			materialList[i] = nullptr;
		}
	}
}

Material* MaterialManager::Get(const char* name, bool creation)
{
	for (int i = 0; i < materialList.size(); i++)
	{
		if (std::string(materialList[i]->name) == std::string(name))
		{
			return materialList[i];
		}
	}

	return NotFound(creation, name);
}

Material* MaterialManager::Get(int index)
{
	return materialList[index] ? materialList[index] : NotFound(false, "---",index);
}

bool MaterialManager::Create(std::string name, Texture* texture)
{
	if (Get(name.c_str(),true) == nullptr)
	{
		//printf("Creating Material with name: %s.\n", name);
		Add(new Material(name, texture));
		return true;
	}

	printf("Material already exist with name: %s.\n", name);
	return false;
}

bool MaterialManager::Create(std::string name, Texture* diffuse, Texture* specular, Texture* normal, Texture* ambient, Texture* rough)
{
	if (Get(name.c_str(), true) == nullptr)
	{
		//printf("Creating Material with name: %s.\n", name);
		Add(new Material(name, diffuse, specular, normal, ambient, rough));
		return true;
	}

	printf("Material already exist with name: %s.\n", name);
	return false;
}

void MaterialManager::Create(std::string name, std::string diffuseName, std::string specularName, std::string normalName, std::string ambientName, std::string roughName)
{
	if (Get(name.c_str(), true) == nullptr)
	{
		Add(new Material(name.c_str(), textureManager->Get(diffuseName.c_str(), TEXTURETYPE::Diffuse), textureManager->Get(specularName.c_str(), TEXTURETYPE::Specular), textureManager->Get(normalName.c_str(), TEXTURETYPE::Normal), textureManager->Get(ambientName.c_str(), TEXTURETYPE::Ambient), textureManager->Get(roughName.c_str(), TEXTURETYPE::Rough)));
		std::cout << "IMGUI just made a material: " << name << std::endl;
	}
}

void MaterialManager::Create(std::string name, std::string diffuseName, float diffuseStrength, std::string specularName, float specularStrength, std::string normalName, float normalStrength, std::string ambientName, float ambientStrength, std::string roughName, float roughStrength)
{
	if (Get(name.c_str(), true) == nullptr)
	{
		Add(new Material(name.c_str(), textureManager->Get(diffuseName, TEXTURETYPE::Diffuse), diffuseStrength, textureManager->Get(specularName, TEXTURETYPE::Specular),specularStrength, textureManager->Get(normalName, TEXTURETYPE::Normal), normalStrength, textureManager->Get(ambientName, TEXTURETYPE::Ambient), ambientStrength, textureManager->Get(roughName, TEXTURETYPE::Rough), roughStrength));
		std::cout << "IMGUI just made a material: " << name << std::endl;
	}
}

int MaterialManager::GetIndex(std::string name)
{
	SetNames();

	for (int i = 0; i < materialNames.size(); i++)
	{
		if (materialNames[i] == name)
			return i;
	
	}
	return 404;
}

void MaterialManager::SetNames()
{
	materialNames.clear();
	for (int i = 0; i < materialList.size(); i++)
	{
		materialNames.push_back(materialList[i]->name);
	}
}

std::vector<std::string> MaterialManager::GetNames()
{
	SetNames();
	return materialNames;
}

Material* MaterialManager::NotFound(bool creation, const char* name, int index)
{
	if (!creation)
		printf("Material Not Found with name: %s, index: %d.\n", name, index);
	
	return nullptr;
}

bool MaterialManager::Add(Material* newMaterial)
{
	materialList.push_back(newMaterial);
	return true;
}

bool MaterialManager::DebugManager()
{
	printf("Materials: \n");
	for (int i = 0; i < materialList.size(); i++)
	{
		std::cout << " - " << materialList[i]->name << std::endl;
	}
	printf("\n");

	return true;
}

void MaterialManager::SetDirLightDirection(glm::vec3 direction)
{
	for (int i = 0; i < materialList.size(); i++)
	{
		materialList[i]->SetDirectionalLightDirection(direction);
	}
}
