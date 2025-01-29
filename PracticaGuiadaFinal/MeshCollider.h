#pragma once
#include "CapsuleCollider.h"
#include "Triangle.h"
#include <vector>

class MeshCollider : public Collider
{
private:
	std::vector<Triangle> triangles;
    Vector3D minBounds, maxBounds; // Minimum corner of the bounding box

public:
    MeshCollider(const std::vector<Triangle>& meshTriangles)
        : triangles(meshTriangles) 
    {
        CalculateBounds();
    }


    const std::vector<Triangle>& GetTriangles() const {
        return triangles;
    }

    bool CheckCollision(Collider& other) override;
    bool CheckCollisionWithCapsule(CapsuleCollider& capsule);

    void DebugRenderer() override;

    void UpdatePosition(Vector3D newPosition) override;
    void CalculateBounds(); // Calculates bounds from triangles
    bool IsWithinBounds(Collider& other) const;

    void AddTriangle(const Triangle& triangle) {
        triangles.push_back(triangle);
    }
};

