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
    std::cout << "Rendering triangle: ";
    for (const auto& triangle : triangles) {
        const auto& v0 = triangle.getCoords0();
        const auto& v1 = triangle.getCoords1();
        const auto& v2 = triangle.getCoords2();

        glVertex3f(v0.GetX(), v0.GetY(), v0.GetZ());
        glVertex3f(v1.GetX(), v1.GetY(), v1.GetZ());
        glVertex3f(v2.GetX(), v2.GetY(), v2.GetZ());
    }
    glEnd();
}