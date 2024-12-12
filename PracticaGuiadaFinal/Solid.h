#pragma once
#include "Vector3D.h"
#include "Color.h"


class Solid
{
private:

	Vector3D coordinates;

	Color color;

	Vector3D orientation;

	bool isAffectedByGravity = false;

	bool isStationary = false;

	Vector3D orientationSpeed = Vector3D(1,1,0);

	Vector3D speed = Vector3D(0, 0, 0);

public:

	Solid() :coordinates(Vector3D(0.0, 0.0, 0.0)),
		orientation(Vector3D(0, 0, 0)),
		color(Color(0.2, 0.3, 0.4)) {}

	Solid(Vector3D coordinates, Color color, Vector3D orientation) :

		coordinates(coordinates),
		color(color),
		orientation(orientation) {}

	inline Vector3D GetCoordinates() const { return this->coordinates; }
	inline Color GetColor() const { return this->color; }
	inline Vector3D GetOrientation() const { return this->orientation; }
	inline Vector3D GetOrientationSpeed() const { return this->orientationSpeed; }
	inline Vector3D GetSpeed() const { return this->speed; }
	inline bool GetIsAffectedByGravity() const { return this->isAffectedByGravity; }
	inline bool GetIsStationary() const { return this->isAffectedByGravity; }

	inline void SetCoordinates(const Vector3D& coordinatesToSet) { this->coordinates = coordinatesToSet; }
	inline void SetColor(const Color& colorToSet) { this->color = colorToSet; }
	inline void SetOrientation(const Vector3D& orientationToSet) { this->orientation = orientationToSet; }
	inline void SetOrientationSpeed(const Vector3D& orientationSpeedToSet) { this->orientationSpeed = orientationSpeedToSet; }
	inline void SetSpeed(const Vector3D& speedToSet) { this->speed = speedToSet; }
	inline void SetIsStationary(const bool& boolToSet) { this->isAffectedByGravity = boolToSet; }

	virtual void Render() = 0;
	virtual Solid* Clone() = 0;
	virtual void Update(const float& time, const Vector3D& gravity);

	virtual bool CheckCollision(Solid* other);
};

