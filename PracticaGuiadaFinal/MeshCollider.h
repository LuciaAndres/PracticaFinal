#pragma once
#include "Collider.h"
#include "Triangle.h"


class MeshCollider : public Collider
{
private:
	std::vector<Triangle> triangles;

public:
    MeshCollider(const std::vector<Triangle>& meshTriangles)
        : triangles(meshTriangles) {}

    const std::vector<Triangle>& GetTriangles() const {
        return triangles;
    }

    bool CheckCollision(Collider& other) override;
    void DebugRenderer() override;

    void AddTriangle(const Triangle& triangle) {
        triangles.push_back(triangle);
    }
};

