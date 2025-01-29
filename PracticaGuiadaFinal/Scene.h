#pragma once
#include <vector>
#include "Solid.h"
#include "Camera.h"
#include "Vector3D.h"
#include "MeshCollider.h"
#include "UI.h"



class Scene
{

private:
	
	std::vector<Solid*> gameObjects;
	std::vector<std::unique_ptr<Collider>> colliders;

	Camera* camera;

	Vector3D boundary = Vector3D(8, 6, 4);

	void checkBoundary(Solid* object);

	static Scene* instance;
public:
	Scene() : camera(new Camera()), boundary(Vector3D(8, 6, 4)) {}

	Scene(Camera* cameraToSet) : camera(cameraToSet), boundary(Vector3D(8, 6, 4)) {}

	virtual void AddGameObject(Solid* object);
	virtual void AddCollider(std::unique_ptr<Collider> collider);
	virtual MeshCollider* GetScenarioCollider();
	virtual void AddHiddenObject(Solid* object);
	virtual void Update(const float& time);
	virtual void Render();
};



