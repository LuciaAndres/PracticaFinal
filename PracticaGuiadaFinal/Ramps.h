#pragma once
#include "Collider.h"
#include "OBB.h"
#include <cmath>

class Ramps : public Collider {
private:
	Vector3D startPoint, endPoint, controlPoint;
	Vector3D normal;
	OBB boundingBox;

	void RenderDebugSphere(Vector3D position, float radius, float r, float g, float b);
public:
	Ramps(Vector3D start, Vector3D end, Vector3D control);

	bool CheckCollision(const OBB& playerOBB) override;

	float GetRampHeightAt(Vector3D position) {
		// Plane equation: Ax + By + Cz + D = 0
		// Solve for Y: Y = (-Ax - Cz - D) / B
		float A = normal.GetX();
		float B = normal.GetY();
		float C = normal.GetZ();
		float D = -normal.DotProduct(startPoint); // D = -(A*start.x + B*start.y + C*start.z)

		if (std::abs(B) < 1e-6f) {
			// Handle vertical ramps (e.g., return startPoint.GetY())
			return startPoint.GetY();
		}
		return (-A * position.GetX() - C * position.GetZ() - D) / B;
	}

	void DebugRenderer() override;
};
