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
    static OBB FromTriangle( Vector3D& v0,  Vector3D& v1, Vector3D& v2, const Vector3D& offset = Vector3D()) {  
		Vector3D min(
			std::min({ v0.GetX(), v1.GetX(), v2.GetX() }),
			std::min({ v0.GetY(), v1.GetY(), v2.GetY() }),
			std::min({ v0.GetZ(), v1.GetZ(), v2.GetZ() })
		);

		Vector3D max(
			std::max({ v0.GetX(), v1.GetX(), v2.GetX() }),
			std::max({ v0.GetY(), v1.GetY(), v2.GetY() }),
			std::max({ v0.GetZ(), v1.GetZ(), v2.GetZ() })
		);

		Vector3D center = (min + max) * 0.5f + offset;
		Vector3D halfSize = (max - min) * 0.5f;
		Matrix3x3 orientation = Matrix3x3::Identity();

		return OBB(center, halfSize, orientation);
    }
};
