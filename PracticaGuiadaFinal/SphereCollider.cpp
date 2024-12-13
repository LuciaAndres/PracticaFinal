#include "SphereCollider.h"

bool SphereCollider::CheckCollision(Collider& other) 
{
    const SphereCollider* sphere = dynamic_cast<SphereCollider*>(&other);
    if (sphere) {
        float distanceSquared = (this->center - sphere->center).LenghtSquared();
        float radiusSum = radius + sphere->radius;
        return distanceSquared <= (radiusSum * radiusSum);
    }
    return false;
}

void SphereCollider::DebugRenderer() 
{
    glPushMatrix();
    glTranslatef(center.GetX(), center.GetY(), center.GetZ());
    glutWireSphere(radius, 16, 16);
    glPopMatrix();
}
