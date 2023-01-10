#pragma once

#include <iostream>

namespace RayTracing {
	class Vector3
	{
	public:
		double Elements[3];

		Vector3();
		Vector3(double element0, double element1, double element2);


		double X() const;
		double Y() const;
		double Z() const;
		double Length() const;
		double LengthSquared() const;

		Vector3& operator+=(const Vector3& v);
		Vector3 operator-() const;
		Vector3& operator*=(const double t);
		Vector3& operator/=(const double t);
		double operator[](int i) const;
		double& operator[](int i);

		static Vector3 Random();
		static Vector3 Random(double min, double max);

		bool IsNearZero() const;
	};
	using Point3 = Vector3;   // 3D Point
	using Color = Vector3;    // RGB color

	std::ostream& operator<<(std::ostream& out, const Vector3& v);
	Vector3 operator+(const Vector3& u, const Vector3& v);
	Vector3 operator-(const Vector3& u, const Vector3& v);
	Vector3 operator*(const Vector3& u, const Vector3& v);
	Vector3 operator*(double t, const Vector3& v);
	Vector3 operator*(const Vector3& v, double t);
	Vector3 operator/(Vector3 v, double t);
	double Dot(const Vector3& u, const Vector3& v);
	Vector3 Cross(const Vector3& u, const Vector3& v);
	Vector3 UnitVector(Vector3 v);

	Point3 RandomPointInUintSphere();
	Vector3 RandomUnitVector();
	Vector3 RandomInHemisphere(const Vector3& normal);
	
}