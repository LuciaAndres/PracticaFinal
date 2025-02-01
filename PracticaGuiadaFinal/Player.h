#pragma once
#include "util.h"
#include "Solid.h"
#include "FirstPersonCamera.h"
#include "Cuboid.h"
#include "ModelLoader.h"
#include "Scene.h"
#include <math.h>
#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)

class Player : public Solid
{
private:

	int mouseX;
	int mouseY;

	float gravity = -10;

	bool isJumping = false;
	float jumpHeight = 5.0f;
	float verticalSpeed = 0.0f;
	float groundLevel = 2.5f;

	const float INITIAL_SPEED = 0.14f;

	float playerStep = INITIAL_SPEED;

	float Clamp(float value, float min, float max);
	void MoveInDirection(float direction);
	void MoveInDirectionDebug(float direction);
	void StrafeInDirection(float direction);
	void StrafeInDirectionDebug(float direction);
	void UpdateMovement(float deltaTime);
	void UpdateCamera(float deltaTime);
	void ApplyGravity(float deltaTime);

	AABB playerBoundingBox;

	Scene* scene;

	FirstPersonCamera* view;

	bool keys[256] = { false };
	bool fullScreenMode = false;

public:

	Player() :
		mouseX(-1), mouseY(-1),
		view(new FirstPersonCamera(Vector3D(0, 2.5, 0)))
	{
		SetIsStationary(false);
	}
	bool CheckCollision(Solid* other);

	inline FirstPersonCamera* getFPC() const { return this->view; }

	void ProcessMouseMovement(int x, int y);
	void Update(float deltaTime);
	void ProcessKeyPressed(unsigned char key, int px, int py);
	void ProcessKeyReleased(unsigned char key, int px, int py);

	inline float GetMouseX() const { return this->mouseX; }
	inline void SetMouseX(const float& mousexToSet) { this->mouseX = mousexToSet; }

	inline float GetMouseY() const { return this->mouseY; }
	inline void SetMouseY(const float& mouseyToSet) { this->mouseY = mouseyToSet; }

	void SetScene(Scene* newScene) { scene = newScene; }

	Solid* Clone();

	void Render();
};
