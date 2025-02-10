#pragma once
#include "Collider.h"
#include "AABB.h"
class Ramps : public Collider {
private:
	Vector3D startPoint, endPoint, controlPoint;
	Vector3D normal;
	AABB boundingBox;

	void RenderDebugSphere(Vector3D position, float radius, float r, float g, float b);
public:
	Ramps(Vector3D start, Vector3D end, Vector3D control)
		: startPoint(start), endPoint(end), controlPoint(control)
	{
		boundingBox = AABB(
			Vector3D(std::min({ start.GetX(), end.GetX(), control.GetX() }),
				std::min({ start.GetY(), end.GetY(), control.GetY() }),
				std::min({ start.GetZ(), end.GetZ(), control.GetZ() })),

			Vector3D(std::max({ start.GetX(), end.GetX(), control.GetX() }),
				std::max({ start.GetY(), end.GetY(), control.GetY() }),
				std::max({ start.GetZ(), end.GetZ(), control.GetZ() }))
		);

		Vector3D edge1 = end - start;
		Vector3D edge2 = control - start;
		normal = edge2.Cross(edge1).Normalize();
	}

	virtual bool CheckCollision(const AABB& other) override
	{
		return boundingBox.Intersects(other);
	}

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
