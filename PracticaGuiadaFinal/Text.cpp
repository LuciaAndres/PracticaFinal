#include "Text.h"
void Text::Render()
{
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glColor3f(this->GetColor().GetRed(), this->GetColor().GetGreen(), this->GetColor().GetBlue());
	glTranslatef(this->GetCoordinates().GetX(), this->GetCoordinates().GetY(), this->GetCoordinates().GetZ());
	glRasterPos3d(0, 0, 0);
	for (char c : text)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, c);
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

Text* Text::Clone()
{
	return nullptr;
}

void Text::renderOnScreenAt(float x, float y)
{
	glColor3f(this->GetColor().GetRed(), this->GetColor().GetGreen(), this->GetColor().GetBlue());
	glRasterPos2f(x, y); // Set position in screen space
	for (char c : text) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c); // Render each character
	}
}