#pragma once

#include "Ray.h"

using std::shared_ptr;


namespace RayTracing
{
	class Material;

	class HitRecord {
	public:
		Point3 Point;
		Vector3 NormalVector;
		shared_ptr<Material> MaterialPtr;
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
		virtual ~Hittable() = default;

	};

	class Sphere : public Hittable {
	public:
		Point3 Center;
		double Radius;
		shared_ptr<Material> MaterialPtr;

		Sphere();
		Sphere(Point3 center, double radius, shared_ptr<Material> materialPtr);

		bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& hitRecord) const override;
	};

}

