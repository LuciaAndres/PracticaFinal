#include "MeshCollider.h"

void MeshCollider::AddBoundingBox(const AABB& box) {
    boundingBoxes.push_back(box);
}

bool MeshCollider::CheckCollision(const AABB& other) const {
    for (const auto& box : boundingBoxes) {
        if (box.CheckCollision(other)) {
            // Check if the collision is with the floor (by comparing Y values)
            if (other.GetMinBounds().GetY() >= box.GetMaxBounds().GetY() - 0.1f) {
                return true; // Collision with floor
            }
            // If colliding with walls, stop movement
            return true;
        }
    }
    return false;
}

void MeshCollider::GenerateBoundingBoxesFromTriangles(const std::vector<Triangle>& triangles) {
    boundingBoxes.clear(); // Reset existing boxes

    for (const auto& triangle : triangles) {
        // Apply world position offset
        Vector3D worldV0 = triangle.getCoords0() + position;
        Vector3D worldV1 = triangle.getCoords1() + position;
        Vector3D worldV2 = triangle.getCoords2() + position;

        Vector3D minBounds = Vector3D(
            std::min({ worldV0.GetX(), worldV1.GetX(), worldV2.GetX() }),
            std::min({ worldV0.GetY(), worldV1.GetY(), worldV2.GetY() }),
            std::min({ worldV0.GetZ(), worldV1.GetZ(), worldV2.GetZ() })
        );

        Vector3D maxBounds = Vector3D(
            std::max({ worldV0.GetX(), worldV1.GetX(), worldV2.GetX() }),
            std::max({ worldV0.GetY(), worldV1.GetY(), worldV2.GetY() }),
            std::max({ worldV0.GetZ(), worldV1.GetZ(), worldV2.GetZ() })
        );

        boundingBoxes.emplace_back(minBounds, maxBounds);
    }

    //std::cout << "Generated " << boundingBoxes.size() << " bounding boxes for the scenario." << std::endl;
}

void MeshCollider::RenderBoundingBoxes() const {
    for (const auto& box : boundingBoxes) {
        box.DebugRenderer(Color(1,0,0));
    }
}