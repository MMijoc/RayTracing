#pragma once

#include "Ray.h"

namespace RayTracing
{
	typedef struct _hitRecord {
		Point3 point;
		Vector3 normalVector;
		double t;
	} HitRecord;

	class Hittable
	{
	public:
		virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& hitRecord) const = 0;

	private:

	};

	class Sphere : public Hittable {
	public:
		Point3 Center;
		double Radius;

		Sphere();
		Sphere(Point3 center, double radius);

		virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& hitRecord) const override;
	};

}

