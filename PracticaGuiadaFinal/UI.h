#pragma once
#include "Text.h"
#include "Vector3D.h"

class UI
{
private:
	Text fps;
	Text scoreText;

	float fpsUpdateTimer = 5.0f;   // Timer for updating FPS
	int frameCount = 0;

	float screenWidth = 800;
	float screenHeight = 600;
	
	int score = 0;

	void RenderFPS();
	void RenderCrosshair();
	void RenderScore();
public:

	UI() :
		fps("FPS: null"),scoreText("Puntuacion: 0") {
	}

	float getScore() const { return score; }
	void UpdateFPS(float deltaTime);
	void UpdateScore(int newScore);
	void Render();
};
