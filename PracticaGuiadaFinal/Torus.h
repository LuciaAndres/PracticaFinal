#pragma once
#include <GL/glut.h>
#include "Vector3D.h"
#include "Color.h"
#include "Solid.h"

class Torus : public Solid
{
private:

	float internalRadius;
	float externalRadius;
	float faces;
	float rings;

public:

	Torus(Vector3D coordinates, Color color, Vector3D orientation, float internalRadius, float externalRadius, float faces, float rings) :

		Solid(coordinates, color, orientation),
		internalRadius(internalRadius), externalRadius(externalRadius), faces(faces), rings(rings) {}

	inline float GetInternalRadius() const { return this->internalRadius; }
	inline float GetExternalRadius() const { return this->externalRadius; }
	inline float GetFaces() const { return this->faces; }
	inline float GetRings() const { return this->rings; }

	inline void SetInternalRadius(const float& internalRadiusToSet) { this->internalRadius = internalRadiusToSet; }
	inline void SetExternalRadius(const float& externalRadiusToSet) { this->externalRadius = externalRadiusToSet; }
	inline void SetFaces(const float& facesToSet) { this->faces = facesToSet; }
	inline void SetRings(const float& ringsToSet) { this->rings = ringsToSet; }

	Solid* Clone();

	void Render();

};

