#pragma once
#include "Text.h"
#include "Vector3D.h"

class UI
{
private:
	Text fps;
	float fpsUpdateTimer = 5.0f;   // Timer for updating FPS
	int frameCount = 0;

	float screenWidth = 800;
	float screenHeight = 600;

	void RenderFPS();
	void RenderCrosshair();
public:

	UI() :
		fps("FPS: null") {
	}

	void UpdateFPS(float deltaTime);
	void Render();
};
