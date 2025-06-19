#pragma once
#include "util.h"
#include <iostream>

template <class S> class Vector3Dx;

typedef Vector3Dx<float> Vector3D;

typedef Vector3Dx<float> Vector3Df;
typedef Vector3Dx<double> Vector3Dd;
typedef Vector3Dx<int> Vector3Di;

template<class S>class Vector3Dx
{

private:

	S x, y, z;

public:

	Vector3Dx(S x = 0, S y = 0, S z = 0) :
		x(x), y(y), z(z) {}

	inline S GetX() const { return this->x; }
	inline S GetY() const { return this->y; }
	inline S GetZ() const { return this->z; }

	inline void SetX(S d) { x = d; }
	inline void SetY(S d) { y = d; }
	inline void SetZ(S d) { z = d; }

	Vector3Dx<S> Add(Vector3Dx<S>  b);
	Vector3Dx<S> Subtract(Vector3Dx<S> b);
	Vector3Dx<S> Product(S b) const;
	Vector3Dx<S> Divide(S b) const;
	Vector3Dx<S> Cross(Vector3Dx<S> b);
	Vector3Dx<S> Normalize();
	Vector3Dx<S> Abs();


	float DotProduct(Vector3Dx<S> v);
	float Dot(Vector3Dx<S> v);
	S Magnitude();
	S LengthSquared();
	bool isZero();

	Vector3Dx<S> operator+(Vector3Dx<S> v);
	Vector3Dx<S> operator-(Vector3Dx<S> v);
	Vector3Dx<S> operator-(const Vector3Dx<S>& other) const;
	Vector3Dx<S> operator*(S s) const;
	Vector3Dx<S> operator/(S s) const;

	bool operator==(Vector3Dx<S> v);
	template <class T>
	friend std::ostream& operator<<(std::ostream& os, const Vector3Dx<T>& v);

	S operator[](int index) const {
		if (index == 0) return x;
		if (index == 1) return y;
		if (index == 2) return z;
		throw std::out_of_range("Vector3D index out of range");
	}
};

template <class S>
std::ostream& operator<<(std::ostream& os, const Vector3Dx<S>& v) {
	os << "(" << v.GetX() << ", " << v.GetY() << ", " << v.GetZ() << ")";
	return os;
}
