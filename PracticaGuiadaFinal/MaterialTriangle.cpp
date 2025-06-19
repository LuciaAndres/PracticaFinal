#include "MaterialTriangle.h"

void MaterialTriangle::Render() {
	glDisable(GL_COLOR_MATERIAL);
	useMaterial();

	glBegin(GL_TRIANGLES);

	// Vértice 0
	const Vector3D& n0 = getNormal0();
	const Vector3D& v0 = getCoords0();
	glNormal3f(n0.GetX(), n0.GetY(), n0.GetZ());
	glVertex3f(v0.GetX(), v0.GetY(), v0.GetZ());

	// Vértice 1
	const Vector3D& n1 = getNormal1();
	const Vector3D& v1 = getCoords1();
	glNormal3f(n1.GetX(), n1.GetY(), n1.GetZ());
	glVertex3f(v1.GetX(), v1.GetY(), v1.GetZ());

	// Vértice 2
	const Vector3D& n2 = getNormal2();
	const Vector3D& v2 = getCoords2();
	glNormal3f(n2.GetX(), n2.GetY(), n2.GetZ());
	glVertex3f(v2.GetX(), v2.GetY(), v2.GetZ());

	glEnd();
}
void MaterialTriangle::useMaterial() {
	Color ambient = material.GetAmbientColor();
	Color diffuse = material.GetDiffuseColor();
	Color specular = material.GetSpecularColor();

	float MatAmbient[]  = { ambient.GetRed(),  ambient.GetGreen(),  ambient.GetBlue(),  1.0f };
	float MatDiffuse[]  = { diffuse.GetRed(),  diffuse.GetGreen(),  diffuse.GetBlue(),  1.0f };
	float MatSpecular[] = { specular.GetRed(), specular.GetGreen(), specular.GetBlue(), 0.1f };
	float MatShininess  = 60.0f;
	float black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
/*
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   MatAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   MatDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  MatSpecular);
	glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, MatShininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,  black);*/
	glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, MatShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, black); 
}

