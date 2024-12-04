#pragma once
#include <GL/glut.h>
#include "Vector3D.h"
#include "Color.h"
#include "Solid.h"

class Cylinder : public Solid
{
private:

    float baseRadius;
    float topRadius;
    float height;
    float slices;
    float stacks;
    float alpha;

public:

    Cylinder(Vector3D coordinates, Color color, Vector3D orientation, float baseRadius, float topRadius, float height, float slices, float stacks, float alpha)
        : Solid(coordinates, color, orientation),
        baseRadius(baseRadius),
        topRadius(topRadius),
        height(height),
        slices(slices),
        stacks(stacks),
        alpha(alpha) {}

    inline float GetBaseRadius() const { return this->baseRadius; }
    inline float GetTopRadius() const { return this->topRadius; }
    inline float GetHeight() const { return this->height; }
    inline float GetSlices() const { return this->slices; }
    inline float GetStacks() const { return this->stacks; }
    inline float GetAlpha() const { return this->alpha; }

    inline void SetBaseRadius(const float& baseRadiusToSet) { this->baseRadius = baseRadiusToSet; }
    inline void SetTopRadius(const float& topRadiusToSet) { this->topRadius = topRadiusToSet; }
    inline void SetHeight(const float& heightToSet) { this->height = heightToSet; }
    inline void SetSlices(const float& slicesToSet) { this->slices = slicesToSet; }
    inline void SetStacks(const float& stacksToSet) { this->stacks = stacksToSet; }
    inline void SetAlpha(const float& alphaToSet) { this->alpha = alphaToSet; }

    Solid* Clone();

    void Render();

};

