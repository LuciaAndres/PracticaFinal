#include "Teapot.h"

void Teapot::Render()
{
	glPushMatrix();
	glTranslatef(this->GetCoordinates().GetX(), this->GetCoordinates().GetY(), this->GetCoordinates().GetZ());
	glColor3f(this->GetColor().GetRed(), this->GetColor().GetGreen(), this->GetColor().GetBlue());
	glRotatef(this->GetOrientation().GetX(), 1.0, 0.0, 0.0);
	glRotatef(this->GetOrientation().GetY(), 0.0, 1.0, 0.0);
	glRotatef(this->GetOrientation().GetZ(), 0.0, 0.0, 1.0);
	glutSolidTeapot(this->GetSize());
	glPopMatrix();
}

Teapot* Teapot::Clone()
{
	return new Teapot(*this);
}