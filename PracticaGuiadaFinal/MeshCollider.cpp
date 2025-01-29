#include "MeshCollider.h"
#include "CapsuleCollider.h"
bool MeshCollider::CheckCollision(Collider& other) {
    // Handle CapsuleCollider specifically
    if (IsWithinBounds(other))
    {
        CapsuleCollider* capsule = dynamic_cast<CapsuleCollider*>(&other);
        if (capsule) {
            return CheckCollisionWithCapsule(*capsule);
        }
    }
    return false; // Extend for other collider types if needed
}

bool MeshCollider::CheckCollisionWithCapsule(CapsuleCollider& capsule) {
    for (const auto& triangle : triangles) {
        // Transform triangle vertices to world space
        Triangle worldTriangle(
            triangle.getCoords0() + this->GetPosition(),
            triangle.getCoords1() + this->GetPosition(),
            triangle.getCoords2() + this->GetPosition(),
            triangle.getNormal0(),
            triangle.getNormal1(),
            triangle.getNormal2(),
            triangle.getColor0(),
            triangle.getColor1(),
            triangle.getColor2()
        );

        if (worldTriangle.getCoords0() == worldTriangle.getCoords1() ||
            worldTriangle.getCoords1() == worldTriangle.getCoords2() ||
            worldTriangle.getCoords2() == worldTriangle.getCoords0()) {
            std::cout << "Skipping invalid triangle: "
                << worldTriangle.getCoords0() << ", "
                << worldTriangle.getCoords1() << ", "
                << worldTriangle.getCoords2() << std::endl;
            continue;
        }

        if (capsule.CheckCollisionWithTriangle(worldTriangle)) {
            std::cout << "Collision detected with triangle at: "
                << worldTriangle.getCoords0() << ", "
                << worldTriangle.getCoords1() << ", "
                << worldTriangle.getCoords2() << std::endl;
            return true;
        }
    }
    return false; // No collision detected
}

void MeshCollider::DebugRenderer() {
    
    glDisable(GL_LIGHTING);

    glBegin(GL_LINES);

    for (const auto& triangle : triangles) {
        // Assign a random or specific color to each triangle
        glColor3f(1.0f, 0.0f, 0.0f); // Red for the first line
        glVertex3f(triangle.getCoords0().GetX(), triangle.getCoords0().GetY(), triangle.getCoords0().GetZ());
        glVertex3f(triangle.getCoords1().GetX(), triangle.getCoords1().GetY(), triangle.getCoords1().GetZ());

        glColor3f(0.0f, 1.0f, 0.0f); // Green for the second line
        glVertex3f(triangle.getCoords1().GetX(), triangle.getCoords1().GetY(), triangle.getCoords1().GetZ());
        glVertex3f(triangle.getCoords2().GetX(), triangle.getCoords2().GetY(), triangle.getCoords2().GetZ());

        glColor3f(0.0f, 0.0f, 1.0f); // Blue for the third line
        glVertex3f(triangle.getCoords2().GetX(), triangle.getCoords2().GetY(), triangle.getCoords2().GetZ());
        glVertex3f(triangle.getCoords0().GetX(), triangle.getCoords0().GetY(), triangle.getCoords0().GetZ());
    }
    glColor3f(1.0f, 1.0f, 0.0f);
    //BOUNDING BOX
    glVertex3f(minBounds.GetX(), minBounds.GetY(), minBounds.GetZ());
    glVertex3f(maxBounds.GetX(), minBounds.GetY(), minBounds.GetZ());

    glVertex3f(maxBounds.GetX(), minBounds.GetY(), minBounds.GetZ());
    glVertex3f(maxBounds.GetX(), maxBounds.GetY(), minBounds.GetZ());

    glVertex3f(maxBounds.GetX(), maxBounds.GetY(), minBounds.GetZ());
    glVertex3f(minBounds.GetX(), maxBounds.GetY(), minBounds.GetZ());

    glVertex3f(minBounds.GetX(), maxBounds.GetY(), minBounds.GetZ());
    glVertex3f(minBounds.GetX(), minBounds.GetY(), minBounds.GetZ());

    // Back face
    glVertex3f(minBounds.GetX(), minBounds.GetY(), maxBounds.GetZ());
    glVertex3f(maxBounds.GetX(), minBounds.GetY(), maxBounds.GetZ());

    glVertex3f(maxBounds.GetX(), minBounds.GetY(), maxBounds.GetZ());
    glVertex3f(maxBounds.GetX(), maxBounds.GetY(), maxBounds.GetZ());

    glVertex3f(maxBounds.GetX(), maxBounds.GetY(), maxBounds.GetZ());
    glVertex3f(minBounds.GetX(), maxBounds.GetY(), maxBounds.GetZ());

    glVertex3f(minBounds.GetX(), maxBounds.GetY(), maxBounds.GetZ());
    glVertex3f(minBounds.GetX(), minBounds.GetY(), maxBounds.GetZ());

    // Connect front and back faces
    glVertex3f(minBounds.GetX(), minBounds.GetY(), minBounds.GetZ());
    glVertex3f(minBounds.GetX(), minBounds.GetY(), maxBounds.GetZ());

    glVertex3f(maxBounds.GetX(), minBounds.GetY(), minBounds.GetZ());
    glVertex3f(maxBounds.GetX(), minBounds.GetY(), maxBounds.GetZ());

    glVertex3f(maxBounds.GetX(), maxBounds.GetY(), minBounds.GetZ());
    glVertex3f(maxBounds.GetX(), maxBounds.GetY(), maxBounds.GetZ());

    glVertex3f(minBounds.GetX(), maxBounds.GetY(), minBounds.GetZ());
    glVertex3f(minBounds.GetX(), maxBounds.GetY(), maxBounds.GetZ());

    glEnd();

    glEnable(GL_LIGHTING);
}

void MeshCollider::UpdatePosition(Vector3D newPosition){
    Vector3D offset = newPosition - this->GetPosition();
    this->SetPosition(newPosition);

    for (auto& triangle : triangles) {
        triangle.setCoords0(triangle.getCoords0() + offset);
        triangle.setCoords1(triangle.getCoords1() + offset);
        triangle.setCoords2(triangle.getCoords2() + offset);
    }
    CalculateBounds();
}

void MeshCollider::CalculateBounds() {
    if (triangles.empty()) return;

    minBounds = Vector3D(FLT_MAX, FLT_MAX, FLT_MAX);
    maxBounds = Vector3D(-FLT_MAX, -FLT_MAX, -FLT_MAX);

    for (const auto& triangle : triangles) {
        minBounds.SetX(std::min({ minBounds.GetX(), triangle.getCoords0().GetX(), triangle.getCoords1().GetX(), triangle.getCoords2().GetX() }));
        minBounds.SetY(std::min({ minBounds.GetY(), triangle.getCoords0().GetY(), triangle.getCoords1().GetY(), triangle.getCoords2().GetY() }));
        minBounds.SetZ(std::min({ minBounds.GetZ(), triangle.getCoords0().GetZ(), triangle.getCoords1().GetZ(), triangle.getCoords2().GetZ() }));

        maxBounds.SetX(std::max({ maxBounds.GetX(), triangle.getCoords0().GetX(), triangle.getCoords1().GetX(), triangle.getCoords2().GetX() }));
        maxBounds.SetY(std::max({ maxBounds.GetY(), triangle.getCoords0().GetY(), triangle.getCoords1().GetY(), triangle.getCoords2().GetY() }));
        maxBounds.SetZ(std::max({ maxBounds.GetZ(), triangle.getCoords0().GetZ(), triangle.getCoords1().GetZ(), triangle.getCoords2().GetZ() }));
    }
}

bool MeshCollider::IsWithinBounds(Collider& other) const {
    const CapsuleCollider* capsule = dynamic_cast<const CapsuleCollider*>(&other);
    float radius = capsule ? capsule->GetRadius() : 0.0f; // Use 0 if not a CapsuleCollider

    Vector3D otherPos = other.GetPosition();
    return (otherPos.GetX() + radius >= minBounds.GetX() && otherPos.GetX() - radius <= maxBounds.GetX() &&
        otherPos.GetY() + radius >= minBounds.GetY() && otherPos.GetY() - radius <= maxBounds.GetY() &&
        otherPos.GetZ() + radius >= minBounds.GetZ() && otherPos.GetZ() - radius <= maxBounds.GetZ());
}