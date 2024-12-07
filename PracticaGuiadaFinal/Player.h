#pragma once
#include "util.h"
#include "FirstPersonCamera.h"
#include "Cylinder.h"
#include "ModelLoader.h"


class Player
{
private:

	Cylinder CollisionHandler;

	Model* player;

	FirstPersonCamera view;

public:

	Player()
		: CollisionHandler(Vector3D(0, 0, 1), Color(1, 0, 0), Vector3D(0, 0, 0),
			0.5f, 0.5f, 1.8f, 20, 20, 0.0f), 
		player(nullptr) {}
	
	bool CheckCollision(Solid* other);

	inline FirstPersonCamera getFPS() const { return this->view; }
};

