
#include "Cylinder.h"

void Cylinder::Render()
{
	GLUquadricObj* quadricTemp = gluNewQuadric();
	glPushMatrix();
	glTranslatef(this->GetCoordinates().GetX(), this->GetCoordinates().GetY(), this->GetCoordinates().GetZ());
	glColor4f(this->GetColor().GetRed(), this->GetColor().GetGreen(), this->GetColor().GetBlue(), GetAlpha());
	glRotatef(this->GetOrientation().GetX(), 1.0, 0.0, 0.0);
	glRotatef(this->GetOrientation().GetY(), 0.0, 1.0, 0.0);
	glRotatef(this->GetOrientation().GetZ(), 0.0, 0.0, 1.0);
	gluCylinder(quadricTemp, GetBaseRadius(), GetTopRadius(), GetHeight(), GetSlices(), GetStacks());
	glPopMatrix();
	gluDeleteQuadric(quadricTemp);
}

Solid* Cylinder::Clone()
{
	return new Cylinder(*this);
}