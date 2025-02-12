#pragma once
#include "SphereCollider.h"
#include "Collider.h"
#include "Vector3D.h"
#include "Triangle.h"
#include <math.h>
#include <GL/glut.h>

class CapsuleCollider : public Collider
{
private:

    Vector3D start;
    Vector3D end;

    float radius;

    bool CapsuleCapsuleCollision(CapsuleCollider& other);
    float ClosestDistanceBetweenSegments(Vector3D& p1, Vector3D& q1,
        Vector3D& p2, Vector3D& q2,
        Vector3D& c1, Vector3D& c2);
    float Clamp(float value, float min, float max);

public:
    CapsuleCollider() : start(Vector3D(0,0,0)), end(Vector3D(0,1,0)), radius(1) {}

    CapsuleCollider(Vector3D start, Vector3D end, float radius)
        : start(start), end(end), radius(radius) {}

  //  bool CheckCollision(const AABB& other) override;
    bool CheckCollisionWithTriangle(Triangle& triangle);

    void DebugRenderer() override;
    inline float GetRadius() const { return this->radius; }
    void Update();
};

