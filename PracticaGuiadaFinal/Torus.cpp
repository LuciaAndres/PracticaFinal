#include "Torus.h"

void Torus::Render()
{
	glPushMatrix();
	glTranslatef(this->GetCoordinates().GetX(), this->GetCoordinates().GetY(), this->GetCoordinates().GetZ());
	glColor3f(this->GetColor().GetRed(), this->GetColor().GetGreen(), this->GetColor().GetBlue());
	glRotatef(this->GetOrientation().GetX(), 1.0, 0.0, 0.0);
	glRotatef(this->GetOrientation().GetY(), 0.0, 1.0, 0.0);
	glRotatef(this->GetOrientation().GetZ(), 0.0, 0.0, 1.0);
	glutSolidTorus(this->GetInternalRadius(), this->GetExternalRadius(), this->GetFaces(), this->GetRings());
	glPopMatrix();
}

Solid* Torus::Clone()
{
	return new Torus(*this);
}