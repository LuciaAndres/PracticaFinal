#pragma once
#include "Vector3D.h"

class Collider
{
private:

	Vector3D position;
	float scale;
	Vector3D orientation;

public:
	Collider() {}
	virtual bool CheckCollision(Collider& other) = 0;
	virtual void DebugRenderer() = 0;
	virtual ~Collider() {}

	inline void SetPosition(const Vector3D& positionToSet) { this->position = positionToSet; }
	inline virtual Vector3D GetPosition()  { return this->position; }
	inline virtual void SetScale(float newScale) {scale = newScale;}
	inline virtual float GetScale()  { return this->scale; }
	inline virtual void SetOrientation(Vector3D& newOrientation) { orientation = newOrientation; }
	inline virtual Vector3D GetOrientation()  { return this->position; }
};

