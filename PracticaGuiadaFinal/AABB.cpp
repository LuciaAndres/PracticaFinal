#include "AABB.h"

bool AABB::CheckCollision(const AABB& other) const
{
    return (minBounds.GetX() <= other.maxBounds.GetX() && maxBounds.GetX() >= other.minBounds.GetX()) &&
        (minBounds.GetY() <= other.maxBounds.GetY() && maxBounds.GetY() >= other.minBounds.GetY()) &&
        (minBounds.GetZ() <= other.maxBounds.GetZ() && maxBounds.GetZ() >= other.minBounds.GetZ());
}

void AABB::DebugRenderer(Color color) const {

    glDisable(GL_LIGHTING);
    glColor3f(color.GetRed(), color.GetGreen(), color.GetBlue()); // Red color for bounding box
    glBegin(GL_LINES);

    // Front face
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

bool AABB::Intersects(const AABB& other) const
{
	return (minBounds.GetX() <= other.maxBounds.GetX() && maxBounds.GetX() >= other.minBounds.GetX()) &&
		(minBounds.GetY() <= other.maxBounds.GetY() && maxBounds.GetY() >= other.minBounds.GetY()) &&
		(minBounds.GetZ() <= other.maxBounds.GetZ() && maxBounds.GetZ() >= other.minBounds.GetZ());
}