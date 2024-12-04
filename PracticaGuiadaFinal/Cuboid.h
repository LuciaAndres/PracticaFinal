#pragma once
#include <GL/glut.h>
#include "Color.h"
#include "Vector3D.h"
#include "Solid.h"

class Cuboid : public Solid
{
private:

	float length;
	float height;
	float width;

public:

	Cuboid(Vector3D coordinates, Color color, Vector3D orientation, float length, float height, float width) :


		Solid(coordinates, color, orientation),
		length(length), height(height), width(width) {}


	inline float GetLength() const { return this->length; }
	inline float GetHeight() const { return this->height; }
	inline float GetWidth() const { return this->width; }
	inline void SetLength(const float& sizeToSet) { this->length = sizeToSet; }
	inline void SetHeight(const float& sizeToSet) { this->height = sizeToSet; }
	inline void SetWidth(const float& sizeToSet) { this->width = sizeToSet; }

	Cuboid* Clone();
	
	void Render();

};

