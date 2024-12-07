#include "MaterialTriangle.h"

void MaterialTriangle::Render() {
	glDisable(GL_COLOR_MATERIAL);
	this->useMaterial();
	glBegin(GL_TRIANGLES);
	glNormal3f(this->getNormal0().GetX(), this->getNormal0().GetY(), this -> getNormal0().GetZ());
glVertex3f(this->getCoords0().GetX(), this->getCoords0().GetY(), this -> getCoords0().GetZ());
glNormal3f(this->getNormal1().GetX(), this->getNormal1().GetY(), this -> getNormal1().GetZ());
glVertex3f(this->getCoords1().GetX(), this->getCoords1().GetY(), this -> getCoords1().GetZ());
glNormal3f(this->getNormal2().GetX(), this->getNormal2().GetY(), this -> getNormal2().GetZ());
glVertex3f(this->getCoords2().GetX(), this->getCoords2().GetY(), this -> getCoords2().GetZ());
glEnd();
}

void MaterialTriangle::useMaterial()
{
	float MatAmbient[] = { this->material.GetAmbientColor().GetRed(), this -> material.GetAmbientColor().GetGreen(), this->material.GetAmbientColor().GetBlue(), 1.0f };
	float MatDiffuse[] = { this->material.GetDiffuseColor().GetRed(), this -> material.GetDiffuseColor().GetGreen(), this->material.GetDiffuseColor().GetBlue(), 1.0f };
	float MatSpecular[] = { this->material.GetSpecularColor().GetRed(), this -> material.GetSpecularColor().GetGreen(), this->material.GetSpecularColor().GetBlue(), 0.1f };
	float MatShininess = 60;
	float black[] = { 0.0f,0.0f,0.0f,1.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MatAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MatDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MatSpecular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, MatShininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
}