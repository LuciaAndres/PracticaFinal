#pragma once
#include "Camera.h"
#define _USE_MATH_DEFINES
#include <math.h>
#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0) 
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)

class FirstPersonCamera : public Camera
{
private:
	int mouseX;
	int mouseY;

	Vector3D calcSpeedVector();

	float cameraStep;

public:

	FirstPersonCamera(Vector3D positionArgument = Vector3D()) : Camera(positionArgument), mouseX(-1), mouseY(-1), cameraStep(0.25) { };
	void Render();
	void Update(const float& time);

	void ProcessMouseMovement(int x, int y);
	void ProcessKeyPressed(unsigned char key, int px, int py);

	inline float GetMouseX() const { return this->mouseX; }
	inline void SetMouseX(const float& mousexToSet) { this->mouseX = mousexToSet; }

	inline float GetMouseY() const { return this->mouseY; }
	inline void SetMouseY(const float& mouseyToSet) { this->mouseY = mouseyToSet; }
};

