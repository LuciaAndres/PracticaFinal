#pragma once
#include "Collider.h"
#include "Vector3D.h"
#include "Solid.h"
#include <GL/glut.h>

class SphereCollider : public Collider
{
private:

    Vector3D center;
    float radius;

public:

    SphereCollider() : Collider(), center(Vector3D(0, 0, 0)), radius(1.0f) {}

    SphereCollider(Vector3D center, float radius) : Collider(), center(center), radius(radius) {}

    bool CheckCollision(const OBB& other) override { return false; }

    void DebugRenderer() override;

    inline Vector3D GetCenter() const { return this->center; }
    inline float GetRadius() const { return this->radius; }
};
