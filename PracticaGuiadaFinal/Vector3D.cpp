#include "Vector3D.h"
#include <math.h>

template class Vector3Dx<float>;  
template class Vector3Dx<double>; 
template class Vector3Dx<int>;

template <class S> Vector3Dx<S> Vector3Dx<S>::Add(Vector3Dx<S> b)
{
	return Vector3Dx<S>(this->GetX() + b.GetX(), this->GetY() + b.GetY(), this->GetZ() + b.GetZ());
}

template <class S> Vector3Dx<S> Vector3Dx<S>::Subtract(Vector3Dx<S> v)
{
	return Vector3Dx<S>(this->GetX() - v.GetX(), this->GetY() - v.GetY(), this->GetZ() - v.GetZ());
}

template <class S> Vector3Dx<S> Vector3Dx<S>::Product(S b) const
{
	return Vector3Dx<S>(this->GetX() * b, this->GetY() * b, this->GetZ() * b);
}

template <class S> Vector3Dx<S> Vector3Dx<S>::Divide(S b) const
{
	return Vector3Dx<S>(this->GetX() / b, this->GetY() / b, this->GetZ() / b);
}

template <class S> Vector3Dx<S> Vector3Dx<S>::Cross(Vector3Dx<S> v)
{
	return Vector3Dx<S>(this->GetY() * v.GetZ() - this->GetZ() * v.GetY(),
		this->GetZ() * v.GetX() - this->GetX() * v.GetZ(),
		this->GetX() * v.GetY() - this->GetY() * v.GetX());
}

template <class S> Vector3Dx<S> Vector3Dx<S>::Normalize()
{
	float magnitude = this->Magnitude();
		if(magnitude == 0.0f)
		{
			return *this;
		}
	return Vector3Dx<S>(this->GetX() / magnitude,
		this->GetY() / magnitude,
		this->GetZ() / magnitude);
}

template <class S> float Vector3Dx<S>::DotProduct(Vector3Dx<S> v)
{
	return float((this->GetX() * v.GetX()) + (this->GetY() * v.GetY()) + (this->GetZ() * v.GetZ()));
}

template <class S> S Vector3Dx<S>::Magnitude()
{
	return float(sqrt(LengthSquared()));
}
							
template <class S> S Vector3Dx<S>::LengthSquared()
{
	return float(pow(this->GetX(), 2) + pow(this->GetY(), 2) + pow(this->GetZ(), 2));
}
template <class S> bool Vector3Dx<S>::isZero()
{
	return (GetX() == 0 && GetY() == 0 && GetZ() == 0);
}
template <class S> Vector3Dx<S> Vector3Dx<S>::operator+(Vector3Dx<S> v)
{
	return Add(v);
}

template <class S> Vector3Dx<S> Vector3Dx<S>::operator-(Vector3Dx<S> v)
{
	return Subtract(v);
}

template <class S> Vector3Dx<S> Vector3Dx<S>::operator*(S v) const
{
	return Product(v);
}

template <class S> Vector3Dx<S> Vector3Dx<S>::operator/(S v) const
{
	return Divide(v);
}	

template <class S> bool Vector3Dx<S>::operator==(Vector3Dx<S> v)
{
	return this->GetX() == v.GetX() && this->GetY() == v.GetY() && this->GetZ() == v.GetZ();
}
