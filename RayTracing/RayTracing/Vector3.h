#pragma once

namespace RayTracing {
	class Vector3
	{
	public:
		Vector3();
		Vector3(double element0, double element1, double element2);

		double Elements[3];

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

	private:

	};

}