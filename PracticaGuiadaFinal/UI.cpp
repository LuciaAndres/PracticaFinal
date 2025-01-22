#include "UI.h"
void UI::Render()
{
	RenderFPS();
}

void UI::RenderFPS()
{
	screenWidth = glutGet(GLUT_SCREEN_WIDTH);
	screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

	glPushMatrix();
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, screenWidth, 0, screenHeight, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	float windowWidth = glutGet(GLUT_WINDOW_WIDTH);
	float windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
	float xPos = 10;
	float yPos = screenHeight - 60.0f;
	if (windowWidth == screenWidth && windowHeight == screenHeight)
	{
		xPos = 5;
		yPos = screenHeight - 30.0f;	
	}
	fps.SetColor(Color(1, 1, 1));
	fps.renderOnScreenAt(xPos, yPos);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void UI::UpdateFPS(float deltaTime)
{
	fpsUpdateTimer += deltaTime; // Accumulate elapsed time
	frameCount++;                // Count the current frame

	// Update FPS every second
	if (fpsUpdateTimer >= 0.1f) {
		int fpsValue = static_cast<int>(1 / deltaTime); // Calculate average FPS
		fps.setText("FPS: " + std::to_string(fpsValue));
		fpsUpdateTimer = 0.0f;   // Reset the timer
		frameCount = 0;          // Reset the frame count
	}
}