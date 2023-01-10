#pragma once

#include "Ray.h"

namespace RayTracing
{
	class HitRecord;

	class Material
	{
	public:
		virtual bool Scatter (const Ray& rayIn, const HitRecord& hitRecord, Color& attenuation, Ray& scattered) const = 0;
		virtual ~Material() = default;
	};

	class Lambertian : public Material
	{
	public:
		Color Albedo;

		explicit  Lambertian(const Color& color);
		bool Scatter(const Ray& rayIn, const HitRecord& hitRecord, Color& attenuation, Ray& scattered) const override;
	};
}