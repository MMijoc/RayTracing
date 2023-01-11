#pragma once
#include "Material.h"

#include "Hittable.h"

namespace RayTracing
{
	Lambertian::Lambertian(const Color& color)
	{
		Albedo = color;
	}

	bool Lambertian::Scatter(const Ray& rayIn, const HitRecord& hitRecord, Color& attenuation, Ray& scattered) const
	{
		auto scatterDirection = hitRecord.NormalVector + RandomUnitVector();

		// Catch degenerate scatter direction (if random vector is opposite to normal vector they will sum to zero)
		if (scatterDirection.IsNearZero())
			scatterDirection = hitRecord.NormalVector;

		scattered = Ray(hitRecord.Point, scatterDirection);
		attenuation = Albedo;

		return true;
	}

	Metal::Metal(const Color& albedo, const double fuzziness)
	{
		Albedo = albedo;
		Fuzziness = fuzziness;
	}

	bool Metal::Scatter(const Ray& rayIn, const HitRecord& hitRecord, Color& attenuation, Ray& scattered) const
	{
		const Vector3 reflected = Reflect(UnitVector(rayIn.GetDirection()), hitRecord.NormalVector);

		scattered = Ray(hitRecord.Point, reflected + Fuzziness * RandomPointInUintSphere());
		attenuation = Albedo;

		return (Dot(scattered.GetDirection(), hitRecord.NormalVector) > 0);
	}

	Dielectric::Dielectric(double indexOfRefraction)
	{
		IndexOfRefraction = indexOfRefraction;
	}

	bool Dielectric::Scatter(const Ray& rayIn, const HitRecord& hitRecord, Color& attenuation, Ray& scattered) const
	{
		attenuation = Color(1.0, 1.0, 1.0);
		const double refractionRatio = hitRecord.IsFrontFace ? (1.0/IndexOfRefraction) : IndexOfRefraction;

		const Vector3 unitDirection = UnitVector(rayIn.GetDirection());
		const Vector3 refracted = Refract(unitDirection, hitRecord.NormalVector, refractionRatio);

		scattered = Ray(hitRecord.Point, refracted);
		return true;
	}
}
