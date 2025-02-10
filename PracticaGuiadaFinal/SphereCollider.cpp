#include "SphereCollider.h"

bool SphereCollider::CheckCollision(const AABB& other)
{
  return false;
}

void SphereCollider::DebugRenderer()
{
    glPushMatrix();
    glTranslatef(center.GetX(), center.GetY(), center.GetZ());
    glutWireSphere(radius, 16, 16);
    glPopMatrix();
}
