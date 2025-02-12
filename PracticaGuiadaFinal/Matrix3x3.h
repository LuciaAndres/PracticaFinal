#pragma once
#include "Vector3D.h"


class Matrix3x3
{
private:

public:
	float m[3][3];

	Matrix3x3();

	Matrix3x3(float m00, float m01, float m02,
		float m10, float m11, float m12,
		float m20, float m21, float m22);

	Matrix3x3(Vector3D row1, Vector3D row2, Vector3D row3);

	Matrix3x3(const Matrix3x3& other);

	Matrix3x3& operator=(const Matrix3x3& other);
	Matrix3x3 operator*(const Matrix3x3& other) const;
	Matrix3x3 operator*(float scalar) const;
	Vector3D operator*(const Vector3D& v) const;
	Matrix3x3 operator+(const Matrix3x3& other) const;
	Matrix3x3 operator-(const Matrix3x3& other) const;
	Matrix3x3 operator/(float scalar) const;
	Matrix3x3 operator-() const;
	float Determinant() const;
	Matrix3x3 Transpose() const;
	Matrix3x3 Inverse() const;
	float* operator[](int row);
	const float* operator[](int row) const;
	static Matrix3x3 Identity();
	static Matrix3x3 RotationX(float angle);
	static Matrix3x3 RotationY(float angle);
	static Matrix3x3 RotationZ(float angle);
	static Matrix3x3 Scale(float sx, float sy, float sz);
	static Matrix3x3 Translation(float tx, float ty, float tz);
	static Matrix3x3 LookAt(const Vector3D& eye, const Vector3D& target, Vector3D& up);
	static Matrix3x3 Perspective(float fov, float aspect, float near, float far);
	static Matrix3x3 Orthographic(float left, float right, float bottom, float top, float near, float far);
	static Matrix3x3 FromEulerAngles(float pitch, float yaw, float roll);
	static Matrix3x3 FromAxisAngle(const Vector3D& axis, float angle);
	static Matrix3x3 FromEuler(const Vector3D& euler);
	static Matrix3x3 FromToRotation(Vector3D& from, const Vector3D& to);
	static Matrix3x3 FromScale(const Vector3D& scale);
	static Matrix3x3 FromTranslation(const Vector3D& translation);
	static Matrix3x3 FromLookAt(const Vector3D& eye, const Vector3D& target, Vector3D& up);
	static Matrix3x3 FromPerspective(float fov, float aspect, float near, float far);

	inline float GetValue(int row, int col) const { return m[row][col]; }
	const float* GetMatrix() const { return &m[0][0]; }
	inline void Set(int row, int col, float value) { m[row][col] = value; }

};
