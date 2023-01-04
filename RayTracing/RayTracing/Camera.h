#pragma once

#include "Ray.h"

namespace RayTracing
{
	class Camera {
	public:
		Camera() {
			constexpr auto aspectRatio = 16.0 / 9.0;
			constexpr auto viewportHeight = 2.0;
			constexpr auto viewportWidth = aspectRatio * viewportHeight;
			constexpr auto focalLength = 1.0;

			_origin = Point3(0, 0, 0);
			_horizontal = Vector3(viewportWidth, 0.0, 0.0);
			_vertical = Vector3(0.0, viewportHeight, 0.0);
			_lowerLeftCorner = _origin - _horizontal / 2 - _vertical / 2 - Vector3(0, 0, focalLength);
		}

		Ray GetRay(const double u, const double v) const {
			const auto ray = Ray(_origin, _lowerLeftCorner + u * _horizontal + v * _vertical - _origin);
			return ray;
		}

	private:
		Point3 _origin;
		Point3 _lowerLeftCorner;
		Vector3 _horizontal;
		Vector3 _vertical;
	};

}
