#pragma once
#include "util.h"
#include "Solid.h"
#include "FirstPersonCamera.h"
#include "Cylinder.h"
#include "ModelLoader.h"
#include <math.h>
#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0) 
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)

class Player : public Solid
{
private:
	
	int mouseX;
	int mouseY;

	float gravity = -9.81;

	bool isJumping = false;
	float jumpHeight = 5.0f;
	float verticalSpeed = 0.0f;
	float groundLevel = 0.0f;

	const float INITIAL_SPEED = 0.11f;

	float playerStep = INITIAL_SPEED;

	void updateColliderCoords();
	float Clamp(float value, float min, float max);
	void MoveInDirection(float direction);
	void StrafeInDirection(float direction);

	Cylinder Collider;

	FirstPersonCamera* view;

	bool keys[256] = { false };
	bool fullScreenMode = false;
public:

	Player() :
		Collider(Vector3D(0, 0, 1), Color(1, 0, 0), Vector3D(90, 0, 90),
			0.5f, 0.5f, 2.0f, 20, 20, 0.0f),
		mouseX(-1), mouseY(-1),
		view(new FirstPersonCamera(Vector3D(0,0,0)))
	{
		SetIsStationary(false);
	}
	
	bool CheckCollision(Solid* other);

	inline FirstPersonCamera* getFPC() const { return this->view; }


	void ProcessMouseMovement(int x, int y);
	void UpdateMovement(float deltaTime);
	void ProcessKeyPressed(unsigned char key, int px, int py);
	void ProcessKeyReleased(unsigned char key, int px, int py);

	inline float GetMouseX() const { return this->mouseX; }
	inline void SetMouseX(const float& mousexToSet) { this->mouseX = mousexToSet; }

	inline float GetMouseY() const { return this->mouseY; }
	inline void SetMouseY(const float& mouseyToSet) { this->mouseY = mouseyToSet; }


	Solid* Clone();

	void Render();

};



