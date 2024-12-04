#pragma once
#include <iostream>

class Vector3D
{

private:

	float x;
	float y;
	float z;

public:

	Vector3D(float x, float y, float z) :
		x(x), y(y), z(z) {}

	Vector3D() :
		x(0.0), y(0.0), z(0.0) {}

	inline float GetX() const { return this->x; }
	inline float GetY() const { return this->y; }
	inline float GetZ() const { return this->z; }

	inline void SetX(const float& XToSet) { this->x = XToSet; }
	inline void SetY(const float& YToSet) { this->y = YToSet; }
	inline void SetZ(const float& ZToSet) { this->z = ZToSet; }

	Vector3D Add(const Vector3D& b);
	Vector3D Subtract(const Vector3D& b);
	Vector3D Product(const float& b);
	Vector3D Divide(const float& b);
	float DotProduct(const Vector3D& v);
	float Magnitude();

	Vector3D operator+(const Vector3D& vector);
	Vector3D operator-(const Vector3D& vector);
	Vector3D operator*(const float& value);
	Vector3D operator/(const float& value);
	float operator*(const Vector3D& vector);

};

