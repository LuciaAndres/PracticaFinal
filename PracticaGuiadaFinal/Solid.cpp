#include "Solid.h"


void Solid::Update() 
{
	orientation = orientation + orientationSpeed * 1;
	coordinates = coordinates + speed * 1;
}

bool Solid::CheckCollision(Solid* other)
{
	Vector3D diff = this->GetCoordinates() - other->GetCoordinates();
	return diff.Magnitude() < 0.5;
}