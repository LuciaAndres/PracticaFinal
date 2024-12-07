#pragma once
#include <GL/glut.h>
#include "Vector3D.h"
#include "Color.h"
#include "Solid.h"

class Sphere : public Solid
{
private:

	float radius;
	float slices;
	float slacks;

public:
	Sphere(Vector3D coordinates, Color color, Vector3D orientation, float radius, float slices, float slacks) :

		Solid(coordinates, color, orientation),
		radius(radius), slices(slices), slacks(slacks) {}

	Sphere() : Solid(), radius(0.4), slices(50), slacks(50) {}

	inline float GetRadius() const { return this->radius; }
	inline float GetSlices() const { return this->slices; }
	inline float GetSlacks() const { return this->slacks; }
	inline void SetRadius(const float& radiusToSet) { this->radius = radiusToSet; }
	inline void SetSlices(const float& slicesToSet) { this->slices = slicesToSet; }
	inline void SetSlacks(const float& slacksToSet) { this->slacks = slacksToSet; }

	Solid* Clone();

	void Render();
};

