#pragma once
//AXIS ALIGNED BOUNDING BOX
#include "Vector3D.h"
#include <GL/glut.h>

class AABB
{
private:
    Vector3D minBounds;
    Vector3D maxBounds;
public:
    AABB(Vector3D minBounds, Vector3D maxBounds) : minBounds(minBounds), maxBounds(maxBounds) {}
    AABB() : minBounds(Vector3D()), maxBounds(Vector3D()) {}
    inline Vector3D GetMinBounds() const { return this->minBounds; }
    inline Vector3D GetMaxBounds() const { return this->maxBounds; }
    inline void SetMinBounds(Vector3D minBounds) { this->minBounds = minBounds; }
    inline void SetMaxBounds(Vector3D maxBounds) { this->maxBounds = maxBounds; }
    bool CheckCollision(const AABB& other) const;
    void DebugRenderer(Color color) const;
    void UpdatePosition(Vector3D newPosition);

};
