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
	std::unique_ptr<MeshCollider> scenarioCollider;

	Camera* camera;

	Vector3D boundary = Vector3D(8, 6, 4);

	void checkBoundary(Solid* object);

	static Scene* instance;
public:
	Scene() : camera(new Camera()), boundary(Vector3D(8, 6, 4)) {}

	Scene(Camera* cameraToSet) : camera(cameraToSet), boundary(Vector3D(8, 6, 4)) {}

	virtual void AddGameObject(Solid* object);
	virtual MeshCollider* GetScenarioCollider();
	virtual void SetScenarioCollider(std::unique_ptr<MeshCollider> collider);
	virtual void AddHiddenObject(Solid* object);
	virtual void Update(const float& time);
	virtual void Render();
};
