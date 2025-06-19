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
    void RenderBoundingBoxes() const;
	void UpdatePosition(Vector3D newPosition) { position = newPosition; }
	Vector3D GetPosition() { return position; }

    template<typename T>
    void GenerateBoundingBoxesFromTriangles(const std::vector<T>& triangles) {
        boundingBoxes.clear();

        for (const auto& triangle : triangles) {
            Vector3D worldV0 = triangle.getCoords0() + position;
            Vector3D worldV1 = triangle.getCoords1() + position;
            Vector3D worldV2 = triangle.getCoords2() + position;

            Vector3D minBounds(
                std::min({ worldV0.GetX(), worldV1.GetX(), worldV2.GetX() }),
                std::min({ worldV0.GetY(), worldV1.GetY(), worldV2.GetY() }),
                std::min({ worldV0.GetZ(), worldV1.GetZ(), worldV2.GetZ() })
            );

            Vector3D maxBounds(
                std::max({ worldV0.GetX(), worldV1.GetX(), worldV2.GetX() }),
                std::max({ worldV0.GetY(), worldV1.GetY(), worldV2.GetY() }),
                std::max({ worldV0.GetZ(), worldV1.GetZ(), worldV2.GetZ() })
            );

            boundingBoxes.emplace_back(minBounds, maxBounds);
        }
    }
};

