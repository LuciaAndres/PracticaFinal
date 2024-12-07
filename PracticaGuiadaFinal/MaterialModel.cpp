#include "MaterialModel.h"
#include <iostream>

void MaterialModel::AddMaterialTriangle(MaterialTriangle triangle)
{
	this->triangles.push_back(triangle);
}

void MaterialModel::Render()
{
	glPushMatrix();
	glTranslatef(GetCoordinates().GetX(), GetCoordinates().GetY(), GetCoordinates().GetZ());
	glColor3f(GetColor().GetRed(), GetColor().GetGreen(), GetColor().GetBlue());
	glRotatef(GetOrientation().GetX(), 1.0, 0.0, 0.0);
	glRotatef(GetOrientation().GetY(), 0.0, 1.0, 0.0);
	glRotatef(GetOrientation().GetZ(), 0.0, 0.0, 1.0);
	for (MaterialTriangle triangle : this->triangles)
	{
		triangle.Render();
	}
	glPopMatrix();
}

void MaterialModel::Clear()
{
	this->triangles.clear();
}