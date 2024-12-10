#pragma once
#include "util.h"
#include "Solid.h"
#include "FirstPersonCamera.h"
#include "Cylinder.h"
#include "ModelLoader.h"


class Player : public FirstPersonCamera
{
private:
	int mouseX;
	int mouseY;

	Vector3D gravity = Vector3D(0, -9.81, 0);

	float playerStep;

	Cylinder CollisionHandler;

	FirstPersonCamera* view;

public:

	Player(): 
		CollisionHandler(Vector3D(0, 0, 1), Color(1, 0, 0), Vector3D(0, 0, 0),
		0.5f, 0.5f, 1.8f, 20, 20, 0.0f),
		mouseX(-1), mouseY(-1),
		playerStep(0.2),
		view(new FirstPersonCamera(Vector3D(0,0,0))){}
	
	bool CheckCollision(Solid* other);

	inline FirstPersonCamera* getFPS() const { return this->view; }


	void ProcessMouseMovement(int x, int y);
	void ProcessKeyPressed(unsigned char key, int px, int py);

	inline float GetMouseX() const { return this->mouseX; }
	inline void SetMouseX(const float& mousexToSet) { this->mouseX = mousexToSet; }

	inline float GetMouseY() const { return this->mouseY; }
	inline void SetMouseY(const float& mouseyToSet) { this->mouseY = mouseyToSet; }

};



