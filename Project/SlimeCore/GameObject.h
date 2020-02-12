#pragma once
#include "glm.hpp"
#include "ext.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"
#include "Material.h"
#include "Mesh.h"

class GameObject
{
public:
	GameObject(glm::vec3 pos = glm::vec3(1), glm::vec3 scale = glm::vec3(1), glm::vec3 rot = glm::vec3(0), Mesh* mesh = nullptr, Material* material = nullptr);
	
	/*	Creates a primitive shape:
		   Plane:     (No arguments needed). 
		   Cube:      (No arguments needed).
		   Cylinder:  (radius, halfLength, slices).
		   Sphere:    (radius, sectorCount, stackCount).
		   Cone:      f
	 */
	GameObject(glm::vec3 pos = glm::vec3(1), Primitives::TYPE type = Primitives::TYPE::Cube, Texture* texture = nullptr, float argOne = 1.0f, float argTwo = 1.0f, int argThree = 10);

	virtual ~GameObject();

	glm::mat4 GetModel();
	void Update(float deltaTime);
	void Draw(glm::mat4* ProjectionView);

	void SetPos(glm::vec3 newPos);
	void AddRotate(float rotSpeed, glm::vec3 rotDIR);
	void SetScale(glm::vec3 newScale);

protected:
	glm::vec3 position = glm::vec3(1);
	glm::vec3 rotation = glm::vec3(1);
	glm::vec3 scale = glm::vec3(1);

	glm::mat4 model = glm::mat4(1);
	Material* mat = nullptr;
	Mesh* mesh = nullptr;
};

