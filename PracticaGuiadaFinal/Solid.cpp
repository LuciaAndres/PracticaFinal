#include "Solid.h"


void Solid::Update(const float& time, const Vector3D& gravity)
{
	if (this->GetIsStationary())
	{

	}
	else
	{
	if(this->GetIsAffectedByGravity())
	{
		this->SetSpeed(Vector3D(this->GetSpeed() + gravity * time)); //no operator "*" matches these operands --> const en Vector3D
	}
	else
	{
		this->SetSpeed(Vector3D(this->GetSpeed() * time)); //Not equaling a -ive number properl
	}


	this->SetCoordinates(this->GetCoordinates() + this->GetSpeed());
	//this->SetOrientation(this->GetOrientation() + this->GetOrientationSpeed());
	//std::cout << this->GetOrientation().GetX() << ", " << this->GetOrientation().GetY() << std::endl;
	}
}

bool Solid::CheckCollision(Solid* other)
{
	Vector3D diff = this->GetCoordinates() - other->GetCoordinates();
	return diff.Magnitude() < 0.5;
}