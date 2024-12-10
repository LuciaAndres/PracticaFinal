#include "FirstPersonCamera.h"
#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0) 
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)

void FirstPersonCamera::Render()
{
	glRotatef(this->GetOrientation().GetX(), 1, 0, 0);
	glRotatef(this->GetOrientation().GetY(), 0, 1, 0);
	glRotatef(this->GetOrientation().GetZ(), 0, 0, 1);
	glTranslatef(-1 * this->GetCoordinates().GetX(), -1 * this->GetCoordinates().GetY(), -1 * this->GetCoordinates().GetZ());
}


void FirstPersonCamera::Update(const float& time)
{
	const Vector3D& gravity = Vector3D(0, -9.81, 0);  
	this->SetSpeed(this->calcSpeedVector());
	Camera::Update(time, gravity);

}


Vector3D FirstPersonCamera::calcSpeedVector()
{
	float yOrientation = degToRad(this->GetOrientation().GetY());
	float xOrientation = degToRad(this->GetOrientation().GetX());

	//Fly cam
	//float xComponent = sin(yOrientation) * cos(xOrientation);
	//float yComponent = -sin(xOrientation);
	//float zComponent = -cos(yOrientation) * cos(xOrientation);

	//Walking camera
	float xComponent = sin(yOrientation);
	float yComponent = 0;
	float zComponent = -cos (yOrientation);
	
	Vector3D speedVector = { xComponent, yComponent, zComponent };
	return speedVector;
}
