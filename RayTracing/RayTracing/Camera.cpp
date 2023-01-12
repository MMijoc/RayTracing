#include "Camera.h"
#include "RayTracing.h"

namespace RayTracing
{
	Camera::Camera(
		const Point3 lookFrom,
		const Point3 lookAt,
		const Point3 viewUp,
		const double verticalFieldOfView,
		const double aspectRatio,
		const double aperture,
		const double focusDistance)
	{
		const auto theta = DegreesToRadians(verticalFieldOfView);
		const auto h = tan(theta / 2);
		const auto viewportHeight = 2.0 * h;
		const auto viewportWidth = aspectRatio * viewportHeight;

		_w = UnitVector(lookFrom - lookAt);
		_u = UnitVector(Cross(viewUp, _w));
		_v = Cross(_w, _u);

		_origin = lookFrom;
		_horizontal = focusDistance * viewportWidth * _u;
		_vertical = focusDistance * viewportHeight * _v;
		_lowerLeftCorner = _origin - _horizontal / 2 - _vertical / 2 - focusDistance * _w;
		_lensRadius = aperture / 2;

	}

	Ray Camera::GetRay(const double s, const double t) const
	{
		const Vector3 randomInDisk = _lensRadius * RandomPointInUnitDisk();
		const Vector3 offset = _u * randomInDisk.X() + _v * randomInDisk.Y();
		const auto ray = Ray(_origin + offset,_lowerLeftCorner + s * _horizontal + t * _vertical - _origin - offset);

		return ray;
	}
}
