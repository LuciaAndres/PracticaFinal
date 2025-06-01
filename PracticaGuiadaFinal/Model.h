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

	string name = "nullptr";

public:

	Model(Vector3D coordinates, Color color, Vector3D orientation) :
		Solid(coordinates, color, orientation) {
	}

	Model() :
		Solid() {
	}

	Model(string name) :
		Solid(), name(name){
	}


	bool CheckCollisionWithCapsule(CapsuleCollider& capsule);

	void Render();
	void AddTriangle(Triangle triangle);
	const std::vector<Triangle>& GetTriangles() const {
		return triangles;
	}
	inline void SetName(const string& name) { this->name = name; }
	inline string GetName() const { return this->name; }
	void clear();
	void PaintColor(Color color);
	Solid* Clone();
};

