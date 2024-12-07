#pragma once
#include "Vector3D.h"
#include "Color.h"
#include "Solid.h"
#include <GL/glut.h>

class Triangle : public Solid
{
private:

	Color vertex1Color, vertex2Color, vertex3Color;
	Vector3D vertex1Normal, vertex2Normal, vertex3Normal;
	Vector3D vertex1Coords, vertex2Coords, vertex3Coords;

public:

	Triangle(Color vertex1Color, Vector3D vertex1Normal, Vector3D vertex1Coords,
		Color vertex2Color, Vector3D vertex2Normal, Vector3D vertex2Coords,
		Color vertex3Color, Vector3D vertex3Normal, Vector3D vertex3Coords) :

		vertex1Color(vertex1Color), vertex1Normal(vertex1Normal), vertex1Coords(vertex1Coords),
		vertex2Color(vertex2Color), vertex2Normal(vertex2Normal), vertex2Coords(vertex2Coords),
		vertex3Color(vertex3Color), vertex3Normal(vertex3Normal), vertex3Coords(vertex3Coords) {}

	Triangle(Vector3D vertex1Coords, Vector3D vertex2Coords, Vector3D vertex3Coords, Vector3D vertex1Normal, Vector3D vertex2Normal, Vector3D vertex3Normal) :
		vertex1Coords(vertex1Coords), vertex2Coords(vertex2Coords), vertex3Coords(vertex3Coords),
		vertex1Normal(vertex1Normal), vertex2Normal(vertex2Normal), vertex3Normal(vertex3Normal),
		vertex1Color(Color(128,128,128)), vertex2Color(Color(128, 128, 128)), vertex3Color(Color(128, 128, 128)) {}

	Triangle(Vector3D vertex1Coords, Vector3D vertex1Normal, Vector3D vertex2Coords, Vector3D vertex2Normal, Vector3D vertex3Coords, Vector3D vertex3Normal, Color vertex1Color, Color vertex2Color, Color vertex3Color ) :
		vertex1Coords(vertex1Coords), vertex2Coords(vertex2Coords), vertex3Coords(vertex3Coords),
		vertex1Normal(vertex1Normal), vertex2Normal(vertex2Normal), vertex3Normal(vertex3Normal),
		vertex1Color(vertex1Color), vertex2Color(vertex2Color), vertex3Color(vertex3Color) {}

	Triangle* Clone();
	void Render();




	inline Color getColor0() const { return vertex1Color; }
	inline Vector3D getNormal0() const { return vertex1Normal; }
	inline Vector3D getCoords0() const { return vertex1Coords; }

	inline Color getColor1() const { return vertex2Color; }
	inline Vector3D getNormal1() const { return vertex2Normal; }
	inline Vector3D getCoords1() const { return vertex2Coords; }

	inline Color getColor2() const { return vertex3Color; }
	inline Vector3D getNormal2() const { return vertex3Normal; }
	inline Vector3D getCoords2() const { return vertex3Coords; }

	inline void setColor0(const Color& color) { vertex1Color = color; }
	inline void setNormal0(const Vector3D& normal) { vertex1Normal = normal; }
	inline void setCoords0(const Vector3D& coords) { vertex1Coords = coords; }

	inline void setColor1(const Color& color) { vertex2Color = color; }
	inline void setNormal1(const Vector3D& normal) { vertex2Normal = normal; }
	inline void setCoords1(const Vector3D& coords) { vertex2Coords = coords; }

	inline void setColor2(const Color& color) { vertex3Color = color; }
	inline void setNormal2(const Vector3D& normal) { vertex3Normal = normal; }
	inline void setCoords2(const Vector3D& coords) { vertex3Coords = coords; }


};

