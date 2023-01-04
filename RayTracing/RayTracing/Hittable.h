#pragma once

#include "Ray.h"

namespace RayTracing
{
	class HitRecord {
	public:
		Point3 HitPoint;
		Vector3 NormalVector;
		double t = 0;
		bool IsFrontFace = false;

		void SetFaceNormal(const Ray& ray, const Vector3& outwardNormal)
		{
			IsFrontFace = Dot(ray.GetDirection(), outwardNormal) < 0;
			NormalVector = IsFrontFace ? outwardNormal : -outwardNormal;
		}

	};


	class Hittable
	{
	public:
		virtual inline bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& hitRecord) const = 0;

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

