#pragma once
#include "util.h"
#include "Solid.h"
#include "FirstPersonCamera.h"
#include "Cuboid.h"
#include "CapsuleCollider.h"
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
	float groundLevel = 2.5f;

	const float INITIAL_SPEED = 0.14f;

	float playerStep = INITIAL_SPEED;

	void updateColliderCoords();
	float Clamp(float value, float min, float max);
	void MoveInDirection(float direction);
	void StrafeInDirection(float direction);

	std::unique_ptr<CapsuleCollider> playerCollider;

	FirstPersonCamera* view;

	bool keys[256] = { false };
	bool fullScreenMode = false;
public:

	Player() :
		mouseX(-1), mouseY(-1),
		view(new FirstPersonCamera(Vector3D(0,2.5,0)))
	{
		SetIsStationary(false);
		playerCollider = std::make_unique<CapsuleCollider>(Vector3D(0, 0, 0), Vector3D(0, 2.8, 0), 1.0f);
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

	Collider* getCollisionHandler() {
		return playerCollider.get();
	}

	Solid* Clone();

	void Render();

};
