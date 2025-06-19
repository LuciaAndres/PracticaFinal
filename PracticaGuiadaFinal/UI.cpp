#include "UI.h"
void UI::Render()
{
	RenderFPS();
	RenderCrosshair();
	RenderScore();
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

void UI::RenderCrosshair() {

	float width = 2.4f;
	float length = 6.0f;

	glColor3f(1.0f, 1.0f, 1.0f); // White color for the crosshair
	glDisable(GL_LIGHTING);
	glLineWidth(width);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	int centerX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	int centerY = glutGet(GLUT_WINDOW_HEIGHT) / 2;

	glBegin(GL_LINES);
	// Vertical Line
	glVertex2f(centerX, centerY - length);
	glVertex2f(centerX, centerY + length);

	// Horizontal Line
	glVertex2f(centerX - length, centerY);
	glVertex2f(centerX + length, centerY);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void UI::UpdateScore(int newScore) {
	score = newScore;
	scoreText.SetColor(Color(1, 1, 1));
	scoreText.setText("Puntuacion: "+std::to_string(score));
}

void UI::RenderScore()
{
	float width = 2.4f;

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glLineWidth(width);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, screenWidth, 0, screenHeight, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	scoreText.SetColor(Color(1, 1, 1));
	scoreText.renderOnScreenAt(screenWidth - 220, screenHeight - 30); // Ajusta la posición si lo necesitas

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}
