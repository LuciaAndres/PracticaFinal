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
	Scene() :
		boundary(Vector3D(8, 6, 4)) {}

	void AddGameObject(Solid* object);

	

	void Update(const float& time);
	void Render();
};



