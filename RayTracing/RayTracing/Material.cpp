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

}
