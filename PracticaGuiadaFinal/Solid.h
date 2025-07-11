#pragma once
#include "Vector3D.h"
#include "Color.h"


class Solid
{
protected:

	Vector3D coordinates;

	Color color;

	Vector3D orientation;

	bool isAffectedByGravity;
	bool isHidden;
	bool isCollectible;
	bool isStationary;

	Vector3D orientationSpeed = Vector3D(1,1,0);

	Vector3D speed = Vector3D(0, 0, 0);

public:

	Solid() :coordinates(Vector3D(0.0, 0.0, 0.0)),
		orientation(Vector3D(0, 0, 0)),
		color(Color(0.2, 0.3, 0.4)),
		isAffectedByGravity(false),
		isHidden(false),
		isCollectible(false),
		isStationary(false)	{}

	Solid(Vector3D coordinates, Color color, Vector3D orientation) :

		coordinates(coordinates),
		color(color),
		orientation(orientation),
		isAffectedByGravity(false),
		isHidden(false),
		isCollectible(false),
		isStationary(false) {}

	inline Vector3D GetCoordinates() const { return this->coordinates; }
	inline Color GetColor() const { return this->color; }
	inline Vector3D GetOrientation() const { return this->orientation; }
	inline Vector3D GetOrientationSpeed() const { return this->orientationSpeed; }
	inline Vector3D GetSpeed() const { return this->speed; }
	inline bool GetIsAffectedByGravity() const { return this->isAffectedByGravity; }
	inline bool GetIsStationary() const { return this->isStationary; }
	inline bool GetIsHidden() const { return this->isHidden; }
	inline bool GetIsCollectible() const { return this->isCollectible; }

	inline void SetCoordinates(const Vector3D& coordinatesToSet) { this->coordinates = coordinatesToSet; }
	inline void SetColor(const Color& colorToSet) { this->color = colorToSet; }
	inline void SetOrientation(const Vector3D& orientationToSet) { this->orientation = orientationToSet; }
	inline void SetOrientationSpeed(const Vector3D& orientationSpeedToSet) { this->orientationSpeed = orientationSpeedToSet; }
	inline void SetSpeed(const Vector3D& speedToSet) { this->speed = speedToSet; }
	inline void SetIsStationary(const bool& boolToSet) { this->isStationary = boolToSet; }
	inline void SetIsAffectedByGravity(const bool& boolToSet) { this->isAffectedByGravity = boolToSet; }
	inline void SetIsHidden(const bool& boolToSet) { this->isHidden = boolToSet; }
	inline void SetIsCollectible(const bool& boolToSet) { this->isCollectible = boolToSet; }
	virtual void Render() = 0;
	virtual Solid* Clone() = 0;
	virtual void Update(const float& time, const Vector3D& gravity);

	virtual bool CheckCollision(Solid* other);
};

