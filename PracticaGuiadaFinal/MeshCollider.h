#pragma once
#include "AABB.h"
#include "Solid.h"
#include <vector>
#include "Triangle.h"

class MeshCollider
{
private:
    std::vector<AABB> boundingBoxes;
	Vector3D position;

public:
    MeshCollider() {}

    void AddBoundingBox(const AABB& box);
    bool CheckCollision(const AABB& other) const;
    void GenerateBoundingBoxesFromTriangles(const std::vector<Triangle>& triangles);
    void RenderBoundingBoxes() const;
	void UpdatePosition(Vector3D newPosition) { position = newPosition; }
	Vector3D GetPosition() { return position; }
};

