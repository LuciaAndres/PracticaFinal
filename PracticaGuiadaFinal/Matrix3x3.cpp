#include "Matrix3x3.h"
#include <cmath>

Matrix3x3::Matrix3x3()
{
	m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f;
	m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f;
	m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f;
}

Matrix3x3::Matrix3x3(float m00, float m01, float m02,
	float m10, float m11, float m12,
	float m20, float m21, float m22)
{
	m[0][0] = m00; m[0][1] = m01; m[0][2] = m02;
	m[1][0] = m10; m[1][1] = m11; m[1][2] = m12;
	m[2][0] = m20; m[2][1] = m21; m[2][2] = m22;
}

Matrix3x3::Matrix3x3(Vector3D row1, Vector3D row2, Vector3D row3)
{
	m[0][0] = row1.GetX(); m[0][1] = row1.GetY(); m[0][2] = row1.GetZ();
	m[1][0] = row2.GetX(); m[1][1] = row2.GetY(); m[1][2] = row2.GetZ();
	m[2][0] = row3.GetX(); m[2][1] = row3.GetY(); m[2][2] = row3.GetZ();
}

Matrix3x3::Matrix3x3(const Matrix3x3& other)
{
	m[0][0] = other.m[0][0]; m[0][1] = other.m[0][1]; m[0][2] = other.m[0][2];
	m[1][0] = other.m[1][0]; m[1][1] = other.m[1][1]; m[1][2] = other.m[1][2];
	m[2][0] = other.m[2][0]; m[2][1] = other.m[2][1]; m[2][2] = other.m[2][2];
}

Matrix3x3& Matrix3x3::operator=(const Matrix3x3& other)
{
	if (this == &other) return *this;

	m[0][0] = other.m[0][0]; m[0][1] = other.m[0][1]; m[0][2] = other.m[0][2];
	m[1][0] = other.m[1][0]; m[1][1] = other.m[1][1]; m[1][2] = other.m[1][2];
	m[2][0] = other.m[2][0]; m[2][1] = other.m[2][1]; m[2][2] = other.m[2][2];
	return *this;
}

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& other) const
{
	Matrix3x3 result;

	for (int i = 0; i < 3; i++) { // Row of this matrix
		for (int j = 0; j < 3; j++) { // Column of other matrix
			result.m[i][j] = 0;
			for (int k = 0; k < 3; k++) { // Sum over corresponding elements
				result.m[i][j] += m[i][k] * other.m[k][j];
			}
		}
	}

	return result;
}

Matrix3x3 Matrix3x3::operator*(float scalar) const
{
	Matrix3x3 result;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result.m[i][j] = m[i][j] * scalar;
		}
	}
	return result;
}

Vector3D Matrix3x3::operator*(const Vector3D& v) const {
	return Vector3D(
		m[0][0] * v.GetX() + m[0][1] * v.GetY() + m[0][2] * v.GetZ(),
		m[1][0] * v.GetX() + m[1][1] * v.GetY() + m[1][2] * v.GetZ(),
		m[2][0] * v.GetX() + m[2][1] * v.GetY() + m[2][2] * v.GetZ()
	);
}

Matrix3x3 Matrix3x3::operator+(const Matrix3x3& other) const
{
	Matrix3x3 result;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result.m[i][j] = m[i][j] + other.m[i][j];
		}
	}
	return result;
}

Matrix3x3 Matrix3x3::operator-(const Matrix3x3& other) const
{
	Matrix3x3 result;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result.m[i][j] = m[i][j] - other.m[i][j];
		}
	}
	return result;
}

Matrix3x3 Matrix3x3::operator/(float scalar) const
{
	Matrix3x3 result;
	if (scalar == 0) return result;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result.m[i][j] = m[i][j] / scalar;
		}
	}
	return result;
}


Matrix3x3 Matrix3x3::operator-() const
{
	Matrix3x3 result;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result.m[i][j] = -m[i][j];
		}
	}
	return result;
}

float Matrix3x3::Determinant() const {
	return  m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
		m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
		m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
}

Matrix3x3 Matrix3x3::Transpose() const
{
	Matrix3x3 result;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result.m[i][j] = m[j][i];
		}
	}
	return result;
}

Matrix3x3 Matrix3x3::Inverse() const
{
	Matrix3x3 result;
	float det = Determinant();
	if (det == 0) return result;
	float invDet = 1.0f / det;
	result.m[0][0] = (m[1][1] * m[2][2] - m[1][2] * m[2][1]) * invDet;
	result.m[0][1] = (m[0][2] * m[2][1] - m[0][1] * m[2][2]) * invDet;
	result.m[0][2] = (m[0][1] * m[1][2] - m[0][2] * m[1][1]) * invDet;
	result.m[1][0] = (m[1][2] * m[2][0] - m[1][0] * m[2][2]) * invDet;
	result.m[1][1] = (m[0][0] * m[2][2] - m[0][2] * m[2][0]) * invDet;
	result.m[1][2] = (m[0][2] * m[1][0] - m[0][0] * m[1][2]) * invDet;
	result.m[2][0] = (m[1][0] * m[2][1] - m[1][1] * m[2][0]) * invDet;
	result.m[2][1] = (m[0][1] * m[2][0] - m[0][0] * m[2][1]) * invDet;
	result.m[2][2] = (m[0][0] * m[1][1] - m[0][1] * m[1][0]) * invDet;
	return result;
}

float* Matrix3x3::operator[](int row)
{
	return m[row];
}

const float* Matrix3x3::operator[](int row) const
{
	return m[row];
}

Matrix3x3 Matrix3x3::Identity()
{
	return Matrix3x3();
}

Matrix3x3 Matrix3x3::RotationX(float angle)
{
	float c = cos(angle);
	float s = sin(angle);
	return Matrix3x3(
		1, 0, 0,
		0, c, -s,
		0, s, c
	);
}

Matrix3x3 Matrix3x3::RotationY(float angle)
{
	float c = cos(angle);
	float s = sin(angle);
	return Matrix3x3(
		c, 0, s,
		0, 1, 0,
		-s, 0, c
	);
}

Matrix3x3 Matrix3x3::RotationZ(float angle)
{
	float c = cos(angle);
	float s = sin(angle);
	return Matrix3x3(
		c, -s, 0,
		s, c, 0,
		0, 0, 1
	);
}

Matrix3x3 Matrix3x3::Scale(float sx, float sy, float sz)
{
	return Matrix3x3(
		sx, 0, 0,
		0, sy, 0,
		0, 0, sz
	);
}

Matrix3x3 Matrix3x3::Translation(float tx, float ty, float tz)
{
	return Matrix3x3(
		1, 0, tx,
		0, 1, ty,
		0, 0, tz
	);
}

Matrix3x3 Matrix3x3::LookAt(const Vector3D& eye, const Vector3D& target, Vector3D& up)
{
	Vector3D zAxis = (eye - target).Normalize();
	Vector3D xAxis = up.Cross(zAxis).Normalize();
	Vector3D yAxis = zAxis.Cross(xAxis);
	return Matrix3x3(
		xAxis.GetX(), xAxis.GetY(), xAxis.GetZ(),
		yAxis.GetX(), yAxis.GetY(), yAxis.GetZ(),
		zAxis.GetX(), zAxis.GetY(), zAxis.GetZ()
	);
}

Matrix3x3 Matrix3x3::Perspective(float fov, float aspect, float near, float far)
{
	float f = 1.0f / tan(fov * 0.5f);
	return Matrix3x3(
		f / aspect, 0, 0,
		0, f, 0,
		0, 0, (far + near) / (near - far)
	) * Matrix3x3(
		1, 0, 0,
		0, near * 2, 0,
		0, 0, far + near
	);
}

Matrix3x3 Matrix3x3::Orthographic(float left, float right, float bottom, float top, float near, float far)
{
	return Matrix3x3(
		2 / (right - left), 0, 0,
		0, 2 / (top - bottom), 0,
		0, 0, 2 / (far - near)
	) * Matrix3x3(
		1, 0, 0,
		0, 1, 0,
		0, 0, 1
	) * Matrix3x3(
		1, 0, -(right + left) / 2,
		0, 1, -(top + bottom) / 2,
		0, 0, -(far + near) / 2
	);
}

Matrix3x3 Matrix3x3::FromEulerAngles(float pitch, float yaw, float roll)
{
	return RotationX(pitch) * RotationY(yaw) * RotationZ(roll);
}

Matrix3x3 Matrix3x3::FromAxisAngle(const Vector3D& axis, float angle)
{
	float c = cos(angle);
	float s = sin(angle);
	float t = 1 - c;
	float x = axis.GetX();
	float y = axis.GetY();
	float z = axis.GetZ();
	return Matrix3x3(
		t * x * x + c, t * x * y - s * z, t * x * z + s * y,
		t * x * y + s * z, t * y * y + c, t * y * z - s * x,
		t * x * z - s * y, t * y * z + s * x, t * z * z + c
	);
}

Matrix3x3 Matrix3x3::FromEuler(const Vector3D& euler)
{
	return FromEulerAngles(euler.GetX(), euler.GetY(), euler.GetZ());
}

Matrix3x3 Matrix3x3::FromToRotation(Vector3D& from, const Vector3D& to)
{
	Vector3D axis = from.Cross(to);
	float angle = acos(from.DotProduct(to));
	return FromAxisAngle(axis, angle);
}

Matrix3x3 Matrix3x3::FromScale(const Vector3D& scale)
{
	return Scale(scale.GetX(), scale.GetY(), scale.GetZ());
}

Matrix3x3 Matrix3x3::FromTranslation(const Vector3D& translation)
{
	return Translation(translation.GetX(), translation.GetY(), translation.GetZ());
}

Matrix3x3 Matrix3x3::FromLookAt(const Vector3D& eye, const Vector3D& target, Vector3D& up)
{
	Vector3D zAxis = (eye - target).Normalize();
	Vector3D xAxis = up.Cross(zAxis).Normalize();
	Vector3D yAxis = zAxis.Cross(xAxis);
	return Matrix3x3(
		xAxis.GetX(), xAxis.GetY(), xAxis.GetZ(),
		yAxis.GetX(), yAxis.GetY(), yAxis.GetZ(),
		zAxis.GetX(), zAxis.GetY(), zAxis.GetZ()
	);
}

Matrix3x3 Matrix3x3::FromPerspective(float fov, float aspect, float near, float far)
{
	float f = 1.0f / tan(fov * 0.5f);
	return Matrix3x3(
		f / aspect, 0, 0,
		0, f, 0,
		0, 0, (far + near) / (near - far)
	) * Matrix3x3(
		1, 0, 0,
		0, near * 2, 0,
		0, 0, far + near
	);
}

std::ostream& operator<<(std::ostream& os, const Matrix3x3& matrix) {
	os << "[ " << matrix.GetValue(0, 0) << ", " << matrix.GetValue(0, 1) << ", " << matrix.GetValue(0, 2) << " ]\n"
		<< "[ " << matrix.GetValue(1, 0) << ", " << matrix.GetValue(1, 1) << ", " << matrix.GetValue(1, 2) << " ]\n"
		<< "[ " << matrix.GetValue(2, 0) << ", " << matrix.GetValue(2, 1) << ", " << matrix.GetValue(2, 2) << " ]";
	return os;
}

Matrix3x3 Matrix3x3::Normalize()
{
	Vector3D xAxis(m[0][0], m[1][0], m[2][0]);
	Vector3D yAxis(m[0][1], m[1][1], m[2][1]);
	Vector3D zAxis(m[0][2], m[1][2], m[2][2]);

	// Normalize the X-axis
	xAxis = xAxis.Normalize();

	// Orthogonalize Y-axis using Gram-Schmidt
	yAxis = (yAxis - xAxis * xAxis.DotProduct(yAxis)).Normalize();

	// Compute the Z-axis as the cross-product (ensures perpendicularity)
	zAxis = xAxis.Cross(yAxis);

	// Construct the new normalized matrix
	Matrix3x3 result;
	result.m[0][0] = xAxis.GetX(); result.m[0][1] = yAxis.GetX(); result.m[0][2] = zAxis.GetX();
	result.m[1][0] = xAxis.GetY(); result.m[1][1] = yAxis.GetY(); result.m[1][2] = zAxis.GetY();
	result.m[2][0] = xAxis.GetZ(); result.m[2][1] = yAxis.GetZ(); result.m[2][2] = zAxis.GetZ();

	return result;
}