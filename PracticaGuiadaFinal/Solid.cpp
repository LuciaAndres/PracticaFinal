#include "Solid.h"


void Solid::Update(const float& time)
{
	this->SetCoordinates(this->GetCoordinates() + this->GetSpeed() * time);
	this->SetOrientation(this->GetOrientation() + this->GetOrientationSpeed() * time);
}

bool Solid::CheckCollision(Solid* other)
{
	Vector3D diff = this->GetCoordinates() - other->GetCoordinates();
	return diff.Magnitude() < 0.5;
}