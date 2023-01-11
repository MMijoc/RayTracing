#include "Camera.h"
#include "RayTracing.h"

namespace RayTracing
{
	Camera::Camera(const double verticalFieldOfView, const double aspectRatio) {
		const auto theta = DegreesToRadians(verticalFieldOfView);
		const auto h = tan(theta/2);
		const auto viewportHeight = 2.0 * h;
		const auto viewportWidth = aspectRatio * viewportHeight;

		constexpr auto focalLength = 1.0;

		_origin = Point3(0, 0, 0);
		_horizontal = Vector3(viewportWidth, 0.0, 0.0);
		_vertical = Vector3(0.0, viewportHeight, 0.0);
		_lowerLeftCorner = _origin - _horizontal / 2 - _vertical / 2 - Vector3(0, 0, focalLength);
	}

	Ray Camera::GetRay(const double u, const double v) const {
		const auto ray = Ray(_origin, _lowerLeftCorner + u * _horizontal + v * _vertical - _origin);
		return ray;
	}
}
