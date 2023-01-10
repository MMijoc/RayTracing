#pragma once

#include "Ray.h"

namespace RayTracing
{
	struct HitRecord;

	class Material
	{
	public:
		virtual bool Scatter (const Ray& rayIn, const HitRecord& hitRecord, Color& attenuation, Ray& scattered) const = 0;
		virtual ~Material() = default;
	};
}