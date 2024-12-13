#include "CapsuleCollider.h"

bool CapsuleCollider::CheckCollision(Collider& other) {
    CapsuleCollider* capsule = dynamic_cast<CapsuleCollider*>(&other);
    if (capsule) {
        return CapsuleCapsuleCollision(*capsule);
    }

    Triangle* triangle = dynamic_cast<Triangle*>(&other);
    if (triangle) {
        return CheckCollisionWithTriangle(*triangle);
    }

    return false; // Extend for other collision types
}

bool CapsuleCollider::CheckCollisionWithTriangle(Triangle& triangle)
{
    Vector3D closestPointOnTriangle = triangle.GetClosestPointToSegment(start, end);
    float distance = (closestPointOnTriangle - start).Magnitude();

    return distance <= GetRadius();
}

void CapsuleCollider::DebugRenderer() {

    glBegin(GL_LINES);
    glVertex3f(start.GetX(), start.GetY(), start.GetZ());
    glVertex3f(end.GetX(), end.GetY(), end.GetZ());
    glEnd();

    glPushMatrix();
    glTranslatef(start.GetX(), start.GetY(), start.GetZ());
    glutWireSphere(radius, 16, 16);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(end.GetX(), end.GetY(), end.GetZ());
    glutWireSphere(radius, 16, 16);
    glPopMatrix();
}

bool CapsuleCollider::CapsuleCapsuleCollision(CapsuleCollider& other)
{
    Vector3D dir1 = this->end - this->start;
    Vector3D dir2 = other.end - other.start;

    float rSum = radius + other.radius;
    Vector3D closestPoint1, closestPoint2;

    float distSquared = ClosestDistanceBetweenSegments(
        start, end, other.start, other.end, closestPoint1, closestPoint2);

    return distSquared <= (rSum * rSum);
}

float CapsuleCollider::ClosestDistanceBetweenSegments(Vector3D& p1, Vector3D& q1,
    Vector3D& p2, Vector3D& q2,
    Vector3D& c1, Vector3D& c2) {
    Vector3D d1 = q1 - p1;
    Vector3D d2 = q2 - p2;
    Vector3D r = p1 - p2;
    float a = d1.DotProduct(d1);
    float e = d2.DotProduct(d2);
    float f = d2.DotProduct(r);

    float s, t;
    float c = d1.DotProduct(r);
    float b = d1.DotProduct(d2);

    float denom = a * e - b * b;

    if (denom != 0.0f) {
        s = (b * f - c * e) / denom;
    }
    else {
        s = 0.0f;
    }

    t = (b * s + f) / e;

    s = Clamp(s, 0.0f, 1.0f);
    t = Clamp(t, 0.0f, 1.0f);

    c1 = p1 + d1 * s;
    c2 = p2 + d2 * t;

    return (c1 - c2).LenghtSquared();
}

float CapsuleCollider::Clamp(float value, float min, float max)
{
    if (value < min)
    {
        return min;
    }
    else if (value > max) {
        return max;
    }
    return value;
}