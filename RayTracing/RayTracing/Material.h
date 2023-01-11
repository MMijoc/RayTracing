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
		double Fuzziness;

		explicit Metal(const Color& albedo, double fuzziness);


		bool Scatter(const Ray& rayIn, const HitRecord& hitRecord, Color& attenuation, Ray& scattered) const override;
	};


	class Dielectric : public Material {
	public:
		double IndexOfRefraction;

		Dielectric(double indexOfRefraction);

		bool Scatter(const Ray& rayIn, const HitRecord& hitRecord, Color& attenuation, Ray& scattered) const override;
	};
}