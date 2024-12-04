#include "Vector3D.h"
#include <math.h>


template <class S> Vector3Dx<S> Vector3Dx<S>::Add(Vector3D b)
{
	return Vector3Dx<S>(this->GetX() + v.GetX(), this->GetY() + v.GetY(), this->GetZ() + v.GetZ());
}

template <class S> Vector3Dx<S> Vector3Dx<S>::Subtract(Vector3D b)
{
	return Vector3Dx<S>(this->GetX() - v.GetX(), this->GetY() - v.GetY(), this->GetZ() - v.GetZ());
}

template <class S> Vector3Dx<S> Vector3Dx<S>::Product(S b)
{
	return Vector3Dx<S>(this->GetX() * b, this->GetY() * b, this->GetZ() * b);
}

template <class S> Vector3Dx<S> Vector3Dx<S>::Divide(S b)
{
	return Vector3D(this->GetX() / b, this->GetY() / b, this->GetZ() / b);
}

template <class S> float Vector3Dx<S>::DotProduct(Vector3D v)
{
	return float((this->GetX() * v.GetX()) + (this->GetY() * v.GetY()) + (this->GetZ() * v.GetZ()));
}

template <class S> float Vector3Dx<S>::Magnitude()
{
	return S(sqrt(pow(this->GetX(), 2) + pow(this->GetY(), 2) + pow(this->GetZ(), 2)));
}

template <class S> Vector3Dx<S> Vector3Dx<S>::operator+(Vector3Dx<S> v)
{
	return Add(v);
}

template <class S> Vector3Dx<S> Vector3Dx<S>::operator-(Vector3Dx<S> v)
{
	return Subtract(v);
}

template <class S> Vector3Dx<S> Vector3Dx<S>::operator*(S v)
{
	return Product(v);
}

template <class S> Vector3Dx<S> Vector3Dx<S>::operator/(S v)
{
	return Divide(v);
}

template <class S> float Vector3Dx<S>::operator*(Vector3Dx<S> v)
{
	return DotProduct(v);
}