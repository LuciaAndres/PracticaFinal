#pragma once
#include "Vector3D.h"
#include "Matrix3x3.h"
#include "AABB.h"

class OBB
{
public:
	Vector3D center;
	Vector3D halfSize;
	Matrix3x3 orientation;

	OBB(const Vector3D& center, const Vector3D& halfSize, const Matrix3x3& orientation)
		: center(center), halfSize(halfSize), orientation(orientation) {
	}

	OBB() : center(Vector3D()), halfSize(Vector3D()), orientation(Matrix3x3()) {
	}

	AABB ToAABB();
	void DebugRenderer(Color color) const;
	bool Intersects(const OBB& other) const;
};
