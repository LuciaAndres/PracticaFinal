#pragma once
#include <vector>
#include "Solid.h"
#include "Camera.h"
#include "Vector3D.h"


class Scene
{

private:
	
	std::vector<Solid*> gameObjects;

	Camera* camera;

	Vector3D boundary = Vector3D(8, 6, 4);

	void checkBoundary(Solid* object);

public:
	Scene() : camera(new Camera()), boundary(Vector3D(8, 6, 4)) {}

	Scene(Camera* cameraToSet) : camera(cameraToSet), boundary(Vector3D(8, 6, 4)) {}

	virtual void AddGameObject(Solid* object);

	

	virtual void Update(const float& time);
	virtual void Render();
};



