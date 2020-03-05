#pragma once
#include "PointLight.h"
#include "ShaderManager.h"
#include "MaterialManager.h"
#include "MeshManager.h"

class ObjectManager
{
public:
	ObjectManager(MeshManager* meshManager, MaterialManager* matManager, ShaderManager* shaderManager, TextureManager* textureManager, glm::mat4* projectionView, glm::vec3* cameraPos);
	~ObjectManager();

	GameObject* Create(std::string name, int meshIndex, int materialIndex, int shaderIndex, int parent = 0, glm::vec3 pos = glm::vec3(0));
	GameObject* Create(std::string name, std::string meshName, std::string materialName, std::string shaderName, std::string parent, glm::vec3 pos = glm::vec3(0));

	//ImGUI
	void Create(GameObject* parent, std::string name);
	void SetVars(int index, std::string name, bool isStatic, glm::vec3 pos, glm::vec4 rotation, glm::vec3 scale, std::string meshName, std::string materialName, std::string shaderName);
	
	void Swap(int objIndex, int vectorPos);
	void Add(GameObject* gameObject);
	void AddArray(GameObject** gameObject, int amount);
	void AddArray(std::vector<GameObject*> gameObjects);
	int FindIndex(GameObject* object);
	int FindIndex(std::string name);
	void MoveObject(GameObject* obj, int newPos);
	GameObject* Get(int index);
	GameObject* Get(std::string name);
	std::vector<GameObject*> GetVector(int start, int end);
	void SetNamesVector();
	std::vector<std::string> GetNameVector();
	int FindPointLight(GameObject* lightObject);
	void CreatePointLight(std::string name, glm::vec3 pos, GameObject* parent = nullptr);
	void AddPointLight(PointLight* light);

	void UpdateLights(Shader* shader);
	void BindTexture(int objectIndex, TEXTURETYPE type, Texture* texture);
	void SetIntTexture(int objectIndex, TEXTURETYPE type);

	bool DebugManager();
	bool DebugAll();

	bool Draw();
	bool Update(float deltaTime);
	void DeleteObject(GameObject* object);
	std::string GetObjectName(int index);
	std::vector<GameObject*> objects;
	std::vector<PointLight*> pointLights;
	MaterialManager* matManager = nullptr;
	ShaderManager* shaderManager = nullptr;
	TextureManager* textureManager = nullptr;
	MeshManager* meshManager = nullptr;
	Shader* currentShader = nullptr;
	Material* currentMaterial = nullptr;

	Texture* currentTexture[5] = { nullptr,nullptr,nullptr,nullptr,nullptr };
	
	glm::mat4* projectionView;
	std::vector<std::string> names;
	glm::vec3* camPos;
};