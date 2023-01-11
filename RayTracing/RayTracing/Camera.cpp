#include "Camera.h"
#include "RayTracing.h"

namespace RayTracing
{
	Camera::Camera(const Point3 lookFrom, const Point3 lookAt, const Point3 viewUp, const double verticalFieldOfView, const double aspectRatio)
	{
		const auto theta = DegreesToRadians(verticalFieldOfView);
		const auto h = tan(theta / 2);
		const auto viewportHeight = 2.0 * h;
		const auto viewportWidth = aspectRatio * viewportHeight;

		const auto w = UnitVector(lookFrom - lookAt);
		const auto u = UnitVector(Cross(viewUp, w));
		const auto v = Cross(w, u);

		_origin = lookFrom;
		_horizontal = viewportWidth * u;
		_vertical = viewportHeight * v;
		_lowerLeftCorner = _origin - _horizontal / 2 - _vertical / 2 - w;
	}

	Ray Camera::GetRay(const double s, const double t) const
	{
		const auto ray = Ray(_origin, _lowerLeftCorner + s * _horizontal + t * _vertical - _origin);
		return ray;
	}
}
