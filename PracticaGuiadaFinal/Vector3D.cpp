#include "Vector3D.h"
#include <math.h>


Vector3D Vector3D::Add(const Vector3D& b)
{
	return Vector3D(this->x + b.x, this->y + b.y, this->z + b.z);
}

Vector3D Vector3D::Subtract(const Vector3D& b)
{
	return Vector3D(this->x - b.x, this->y - b.y, this->z - b.z);
}

Vector3D Vector3D::Product(const float& b)
{
	return Vector3D(this->x * b, this->y * b, this->z * b);
}

Vector3D Vector3D::Divide(const float& b)
{
	return Vector3D(this->x / b, this->y / b, this->z / b);
}

float Vector3D::DotProduct(const Vector3D& v)
{
	return float((this->x * v.x) + (this->y * v.y) + (this->z * v.z));
}

float Vector3D::Magnitude()
{
	return float(sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2)));
}

Vector3D Vector3D::operator+(const Vector3D& vector)
{
	return Add(vector);
}

Vector3D Vector3D::operator-(const Vector3D& vector)
{
	return Subtract(vector);
}

Vector3D Vector3D::operator*(const float& value)
{
	return Product(value);
}

Vector3D Vector3D::operator/(const float& value)
{
	return Divide(value);
}

float Vector3D::operator*(const Vector3D& vector)
{
	return DotProduct(vector);
}