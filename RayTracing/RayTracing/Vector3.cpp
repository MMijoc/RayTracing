#include <cmath>
#include <iostream>

#include "Vector3.h"

using std::sqrt;

namespace RayTracing {
	Vector3::Vector3()
	{
		for (size_t i = 0; i < 3; i++)
		{
			Elements[0] = 0;
		}
	}

	Vector3::Vector3(const double element0, const double element1, const double element2)
	{
		Elements[0] = element0;
		Elements[1] = element1;
		Elements[2] = element2;
	}

	double Vector3::X() const { return Elements[0]; }

	double Vector3::Y() const { return Elements[1]; }

	double Vector3::Z() const { return Elements[2]; }

	double Vector3::Length() const
	{
		return sqrt(LengthSquared());
	}

	double Vector3::LengthSquared() const
	{
		return
			Elements[0] * Elements[0] +
			Elements[1] * Elements[1] +
			Elements[2] * Elements[2];
	}

	Vector3& Vector3::operator+=(const Vector3& v)
	{
		Elements[0] += v.Elements[0];
		Elements[1] += v.Elements[1];
		Elements[2] += v.Elements[2];

		return *this;
	}

	Vector3 Vector3::operator-() const
	{
		return Vector3(-Elements[0], -Elements[1], -Elements[2]);
	}

	Vector3& Vector3::operator*=(const double t) {
		Elements[0] *= t;
		Elements[1] *= t;
		Elements[2] *= t;

		return *this;
	}

	Vector3& Vector3::operator/=(const double t) {
		return *this *= 1 / t;
	}

	double Vector3::operator[](int i) const
	{
		return Elements[i];
	}

	double& Vector3::operator[](int i) {
		return Elements[i];
	}


	std::ostream& operator<<(std::ostream& out, const Vector3& v) {
		return out << v.Elements[0] << ' ' << v.Elements[1] << ' ' << v.Elements[2];
	}

	Vector3 operator+(const Vector3& u, const Vector3& v) {
		return Vector3(
			u.Elements[0] + v.Elements[0],
			u.Elements[1] + v.Elements[1],
			u.Elements[2] + v.Elements[2]);
	}

	Vector3 operator-(const Vector3& u, const Vector3& v) {
		return Vector3(
			u.Elements[0] - v.Elements[0],
			u.Elements[1] - v.Elements[1],
			u.Elements[2] - v.Elements[2]);
	}

	Vector3 operator*(const Vector3& u, const Vector3& v) {
		return Vector3(
			u.Elements[0] * v.Elements[0],
			u.Elements[1] * v.Elements[1],
			u.Elements[2] * v.Elements[2]);
	}
	
	Vector3 operator*(const double t, const Vector3& v) {
		return Vector3(
			t * v.Elements[0],
			t * v.Elements[1],
			t * v.Elements[2]);
	}

	Vector3 operator*(const Vector3& v, const double t) {
		return t * v;
	}

	Vector3 operator/(const Vector3 v, const double t) {
		return (1 / t) * v;
	}

	double Dot(const Vector3& u, const Vector3& v) {
		return
			u.Elements[0] * v.Elements[0] +
			u.Elements[1] * v.Elements[1] +
			u.Elements[2] * v.Elements[2];
	}

	Vector3 Cross(const Vector3& u, const Vector3& v) {
		return Vector3(
			u.Elements[1] * v.Elements[2] - u.Elements[2] * v.Elements[1],
			u.Elements[2] * v.Elements[0] - u.Elements[0] * v.Elements[2],
			u.Elements[0] * v.Elements[1] - u.Elements[1] * v.Elements[0]);
	}

	Vector3 UnitVector(const Vector3 v) {
		return v / v.Length();
	}

}