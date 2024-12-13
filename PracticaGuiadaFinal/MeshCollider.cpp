#include "MeshCollider.h"
#include "CapsuleCollider.h"
bool MeshCollider::CheckCollision(Collider& other) {
    // Example: Check for Capsule-Mesh Collision
    CapsuleCollider* capsule = dynamic_cast<CapsuleCollider*>(&other);
    if (capsule) {
        for (auto& triangle : triangles) {
            if (capsule->CheckCollisionWithTriangle(triangle)) {
                return true; // Collision detected
            }
        }
    }

    // Extend for other collider types
    return false;
}

void MeshCollider::DebugRenderer() {
    glBegin(GL_TRIANGLES);
    for (const auto& triangle : triangles) {
        const auto& v0 = triangle.getCoords0();
        const auto& v1 = triangle.getCoords1();
        const auto& v2 = triangle.getCoords2();

        Vector3D transformedV0 = GetPosition().Add(Vector3D(v0.GetX(), v0.GetY(), v0.GetZ()));
        Vector3D transformedV1 = GetPosition().Add(Vector3D(v1.GetX(), v1.GetY(), v1.GetZ()));
        Vector3D transformedV2 = GetPosition().Add(Vector3D(v2.GetX(), v2.GetY(), v2.GetZ()));

        glVertex3f(transformedV0.GetX(), transformedV0.GetY(), transformedV0.GetZ());
        glVertex3f(transformedV1.GetX(), transformedV1.GetY(), transformedV1.GetZ());
        glVertex3f(transformedV2.GetX(), transformedV2.GetY(), transformedV2.GetZ());
    }
    glEnd();
}