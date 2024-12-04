#include "Triangle.h"
void Triangle::Render()
{
	glBegin(GL_TRIANGLES);

	//vértice 1
	glColor3f(vertex1Color.GetRed(), vertex1Color.GetGreen(), vertex1Color.GetBlue()); // Color of vertex 1
	glNormal3f(vertex1Normal.GetX(), vertex1Normal.GetY(), vertex1Normal.GetZ()); // Normal of vertex 1
	glVertex3f(vertex1Coords.GetX(), vertex1Coords.GetY(), vertex1Coords.GetZ()); // Coordinates of vertex 1

	//vértice 2
	glColor3f(vertex2Color.GetRed(), vertex2Color.GetGreen(), vertex2Color.GetBlue()); // Color of vertex 2
	glNormal3f(vertex2Normal.GetX(), vertex2Normal.GetY(), vertex2Normal.GetZ()); // Normal of vertex 2
	glVertex3f(vertex2Coords.GetX(), vertex2Coords.GetY(), vertex2Coords.GetZ()); // Coordinates of vertex 2

	//vértice 3
	glColor3f(vertex3Color.GetRed(), vertex3Color.GetGreen(), vertex3Color.GetBlue()); // Color of vertex 3
	glNormal3f(vertex3Normal.GetX(), vertex3Normal.GetY(), vertex3Normal.GetZ()); // Normal of vertex 3
	glVertex3f(vertex3Coords.GetX(), vertex3Coords.GetY(), vertex3Coords.GetZ()); // Coordinates of vertex 3

	glEnd();
}

Triangle* Triangle::Clone()
{
	return nullptr;
}