#pragma once
#include "Triangle.h"
#include "Material.h"
#include <GL/glut.h>

class MaterialTriangle : public Triangle
{
private:
	Material material;

	void useMaterial();

public:
	MaterialTriangle(
		Vector3D vertex0Argument = Vector3D(),
		Vector3D vertex1Argument = Vector3D(),
		Vector3D vertex2Argument = Vector3D(),
		Vector3D normal0Argument = Vector3D(),
		Vector3D normal1Argument = Vector3D(),
		Vector3D normal2Argument = Vector3D(),
		Color color0Argument = Color(1, 0, 0),
		Color color1Argument = Color(0, 1, 0),
		Color color2Argument = Color(0, 0, 1)) : Triangle(vertex0Argument,
			vertex1Argument, vertex2Argument,
			normal0Argument, normal1Argument, normal2Argument, color0Argument,
			color1Argument, color2Argument)

	{}
	MaterialTriangle(
		Vector3D vertex0Argument,
		Vector3D vertex1Argument,
		Vector3D vertex2Argument,
		Vector3D normal0Argument,
		Vector3D normal1Argument,
		Vector3D normal2Argument,
		const Material& materialArgument,
		Color color0Argument = Color(1, 0, 0),
		Color color1Argument = Color(0, 1, 0),
		Color color2Argument = Color(0, 0, 1))
		: Triangle(color0Argument, normal0Argument, vertex0Argument,
			color1Argument, normal1Argument, vertex1Argument,
			color2Argument, normal2Argument, vertex2Argument),
		material(materialArgument)
	{
	}
	MaterialTriangle(Triangle triangle)
		: MaterialTriangle(
			triangle.getCoords0(),
			triangle.getCoords1(),
			triangle.getCoords2(),
			triangle.getNormal0(),
			triangle.getNormal1(),
			triangle.getNormal2())
	{}
	inline Material GetMaterial() const { return this->material; }
	inline void SetMaterial(const Material& materialToSet) {
		this->material =
			materialToSet;
	}
	void Render();
};

