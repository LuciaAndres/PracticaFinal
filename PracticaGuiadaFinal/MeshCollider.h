#pragma once
#include "CapsuleCollider.h"
#include "Triangle.h"


class MeshCollider : public Collider
{
private:
	std::vector<Triangle> triangles;
    Vector3D minBounds; // Minimum corner of the bounding box
    Vector3D maxBounds; // Maximum corner of the bounding box

public:
    MeshCollider(const std::vector<Triangle>& meshTriangles)
        : triangles(meshTriangles) {}

    const std::vector<Triangle>& GetTriangles() const {
        return triangles;
    }

    bool CheckCollision(Collider& other) override;
    void DebugRenderer() override;

    void UpdatePosition(Vector3D newPosition) override;

    void CalculateBounds(); // Calculates bounds from triangles
    bool IsWithinBounds(Collider& other) const;
    bool CheckCollisionWithCapsule(CapsuleCollider& capsule);
    void AddTriangle(const Triangle& triangle) {
        triangles.push_back(triangle);
    }
};

