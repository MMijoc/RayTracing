#include "Hittable.h"

namespace RayTracing
{
	Sphere::Sphere()
	{
		Center = Point3();
		Radius = 0;
	}

	Sphere::Sphere(const Point3 center, const double radius)
	{
		Center = center;
		Radius = radius;
	}

	bool Sphere::Hit(const Ray& ray, const double tMin, double const tMax, HitRecord& hitRecord) const
	{
		const Vector3 oc = ray.GetOrigin() - Center;
		const double a = ray.GetDirection().LengthSquared();
		const double bHalf = Dot(oc, ray.GetDirection());
		const double c = oc.LengthSquared() - Radius * Radius;
		const double discriminant = bHalf * bHalf -  a * c;

		if (discriminant < 0) {
			return false;
		}

		const double sqrtD = sqrt(discriminant);

		// Find the nearest root that lies in the acceptable range.
		auto root = (-bHalf - sqrtD) / a;
		if (root < tMin || tMax < root) {
			root = (-bHalf + sqrtD) / a;
			if (root < tMin || tMax < root)
				return false;
		}

		hitRecord.t = root;
		hitRecord.HitPoint = ray.At(hitRecord.t);
		const Vector3 outwardNormal = (hitRecord.HitPoint - Center) / Radius;
		hitRecord.SetFaceNormal(ray, outwardNormal);

		return true;
	}

}