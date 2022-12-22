#include "Hittable.h"

namespace RayTracing
{
	Sphere::Sphere()
	{
		Center = Point3();
		Radius = 0;
	}

	Sphere::Sphere(Point3 center, double radius)
	{
		Center = center;
		Radius = radius;
	}

	bool Sphere::Hit(const Ray& ray, double tMin, double tMax, HitRecord& hitRecord) const
	{
		Vector3 oc = ray.GetOrigin() - Center;
		double a = ray.GetDirection().LengthSquared();
		double bHalf = Dot(oc, ray.GetDirection());
		double c = oc.LengthSquared() - Radius * Radius;
		double discriminant = bHalf * bHalf -  a * c;

		if (discriminant < 0) {
			return false;
		}

		double sqrtd = sqrt(discriminant);

		// Find the nearest root that lies in the acceptable range.
		auto root = (-bHalf - sqrtd) / a;
		if (root < tMin || tMax < root) {
			root = (-bHalf + sqrtd) / a;
			if (root < tMin || tMax < root)
				return false;
		}

		hitRecord.t = root;
		hitRecord.point = ray.At(hitRecord.t);
		Vector3 outwardNormal = (hitRecord.point - Center) / Radius;
		hitRecord.SetFaceNormal(ray, outwardNormal);

		return true;
	}

}