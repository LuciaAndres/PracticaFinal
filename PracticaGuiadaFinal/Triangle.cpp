#include "Triangle.h"
void Triangle::Render()
{
	glBegin(GL_TRIANGLES);

	//vértice 1
	glColor3f(vertex1Color.GetRed(), vertex1Color.GetGreen(), vertex1Color.GetBlue()); // Color of vertex 1
	glNormal3f(vertex1Normal.GetX(), vertex1Normal.GetY(), vertex1Normal.GetZ()); // Normal of vertex 1
	glVertex3f(vertex1Coords.GetX(), vertex1Coords.GetY(), vertex1Coords.GetZ()); // Coordinates of vertex 1

	//vértice 2
	glColor3f(vertex2Color.GetRed(), vertex2Color.GetGreen(), vertex2Color.GetBlue()); // Color of vertex 2
	glNormal3f(vertex2Normal.GetX(), vertex2Normal.GetY(), vertex2Normal.GetZ()); // Normal of vertex 2
	glVertex3f(vertex2Coords.GetX(), vertex2Coords.GetY(), vertex2Coords.GetZ()); // Coordinates of vertex 2

	//vértice 3
	glColor3f(vertex3Color.GetRed(), vertex3Color.GetGreen(), vertex3Color.GetBlue()); // Color of vertex 3
	glNormal3f(vertex3Normal.GetX(), vertex3Normal.GetY(), vertex3Normal.GetZ()); // Normal of vertex 3
	glVertex3f(vertex3Coords.GetX(), vertex3Coords.GetY(), vertex3Coords.GetZ()); // Coordinates of vertex 3

	glEnd();
}

Vector3D Triangle::GetClosestPointToSegment(Vector3D& start, Vector3D& end) {
    Vector3D edge1 = vertex2Coords - vertex1Coords;
    Vector3D edge2 = vertex3Coords - vertex1Coords;
    Vector3D normal = edge1.Cross(edge2).Normalize();

    Vector3D segmentDir = end - start;
    float t = (vertex1Coords - start).DotProduct(normal) / segmentDir.DotProduct(normal);

    if (t < 0) t = 0;
    if (t > 1) t = 1;

    Vector3D projectionPoint = start + segmentDir * t;

    if (PointInTriangle(projectionPoint)) {
        return projectionPoint;
    }

    Vector3D closestPoint = vertex1Coords;
    float closestDist = (projectionPoint - vertex1Coords).Magnitude();

    Vector3D tempPoint;
    float tempDist;

    tempPoint = ClosestPointOnSegment(projectionPoint, vertex2Coords, vertex3Coords);
    tempDist = (projectionPoint - tempPoint).Magnitude();
    if (tempDist < closestDist) {
        closestDist = tempDist;
        closestPoint = tempPoint;
    }

    tempPoint = ClosestPointOnSegment(projectionPoint, vertex1Coords, vertex2Coords);
    tempDist = (projectionPoint - tempPoint).Magnitude();
    if (tempDist < closestDist) {
        closestDist = tempDist;
        closestPoint = tempPoint;
    }

    tempPoint = ClosestPointOnSegment(projectionPoint, vertex3Coords, vertex1Coords);
    tempDist = (projectionPoint - tempPoint).Magnitude();
    if (tempDist < closestDist) {
        closestDist = tempDist;
        closestPoint = tempPoint;
    }

    return closestPoint;
}

bool Triangle::PointInTriangle(Vector3D& point) {
    Vector3D edge1 = vertex2Coords - vertex1Coords;
    Vector3D edge2 = vertex3Coords - vertex1Coords;
    Vector3D edge3 = vertex1Coords - vertex3Coords;

    Vector3D c1 = point - vertex1Coords;
    Vector3D c2 = point - vertex2Coords;
    Vector3D c3 = point - vertex3Coords;

    if (edge1.Cross(c1).DotProduct(edge1.Cross(edge2)) >= 0 &&
        edge2.Cross(c2).DotProduct(edge2.Cross(edge3)) >= 0 &&
        edge3.Cross(c3).DotProduct(edge3.Cross(edge1)) >= 0) {
        return true;
    }

    return false;
}

Vector3D Triangle::ClosestPointOnSegment(Vector3D& point, Vector3D& segStart, Vector3D& segEnd) {
    Vector3D segmentDir = segEnd - segStart;
    float t = (point - segStart).DotProduct(segmentDir) / segmentDir.DotProduct(segmentDir);
    t = Clamp(t, 0.0f, 1.0f);
    return segStart + segmentDir * t;
}

float Triangle::Clamp(float value, float min, float max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

Triangle* Triangle::Clone()
{
	return nullptr;
}