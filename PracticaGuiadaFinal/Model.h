#pragma once
#include <GL/glut.h>
#include "Vector3D.h"
#include "Color.h"
#include "Solid.h"
#include <vector>
#include "Triangle.h"
#include "CapsuleCollider.h"
#include "MeshCollider.h"

class Model : public Solid
{
private:

	std::vector<Triangle> triangles;

public:

	Model(Vector3D coordinates, Color color, Vector3D orientation) :
		Solid(coordinates, color, orientation) {}

	Model() :
		Solid() {}


	bool CheckCollisionWithCapsule(CapsuleCollider& capsule);

	void Render();
	void AddTriangle(Triangle triangle);
	const std::vector<Triangle>& GetTriangles() const {
		return triangles;
	}

	void Clear();
	void PaintColor(Color color);
	Solid* Clone();
};

