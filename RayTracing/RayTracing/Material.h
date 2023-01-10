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

		explicit  Lambertian(const Color& albedo);


		bool Scatter(const Ray& rayIn, const HitRecord& hitRecord, Color& attenuation, Ray& scattered) const override;
	};

	class Metal : public Material {
	public:
		Color Albedo;

		explicit Metal(const Color& albedo);


		bool Scatter(const Ray& rayIn, const HitRecord& hitRecord, Color& attenuation, Ray& scattered) const override;
	};

}