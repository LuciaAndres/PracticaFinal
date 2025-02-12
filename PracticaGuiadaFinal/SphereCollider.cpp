#include "SphereCollider.h"

void SphereCollider::DebugRenderer()
{
    glPushMatrix();
    glTranslatef(center.GetX(), center.GetY(), center.GetZ());
    glutWireSphere(radius, 16, 16);
    glPopMatrix();
}
