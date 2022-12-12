#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>
#include <iostream>

using std::sqrt;

class Vector3
{
public:
	// Fields
	double elements[3];

	// Methods
	double x() const { return elements[0]; }
	double y() const { return elements[1]; }
	double z() const { return elements[2]; }
	double length() const
	{
		return sqrt(lengthSquared());
	}
	double lengthSquared() const
	{
		return elements[0] * elements[0] +
			elements[1] * elements[1] +
			elements[2] * elements[2];
	}

	// Constructors
	Vector3()
	{
		for (size_t i = 0; i < 3; i++)
		{
			elements[0] = 0;
		}
	}
	Vector3(double element0, double element1, double element2)
	{
		elements[0] = element0;
		elements[1] = element1;
		elements[2] = element2;
	}

	// operator overloads
	double operator[](int i) const
	{
		return elements[i];
	}

	double& operator[](int i) {
		return elements[i];
	}

	Vector3& operator+=(const Vector3& v)
	{
		elements[0] += v.elements[0];
		elements[1] += v.elements[1];
		elements[2] += v.elements[2];
		return *this;
	}

	Vector3 operator-() const
	{
		return Vector3(-elements[0], -elements[1], -elements[2]);
	}

	Vector3& operator*=(const double t) {
		elements[0] *= t;
		elements[1] *= t;
		elements[2] *= t;
		return *this;
	}

	Vector3& operator/=(const double t) {
		return *this *= 1 / t;
	}
};

// Type aliases for Vector3
using Point3 = Vector3;   // 3D point
using Color = Vector3;    // RGB color

#endif