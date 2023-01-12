#pragma once

#include "Ray.h"

namespace RayTracing
{
	class Camera {
	public:
		Camera(
			Point3 lookFrom,
			Point3 lookAt,
			Point3 viewUp,
			double verticalFieldOfView,
			double aspectRatio,
			double aperture,
			double focusDistance);

		Ray GetRay(double s, double t) const;

	private:
		Point3 _origin;
		Point3 _lowerLeftCorner;
		Vector3 _horizontal;
		Vector3 _vertical;
		Vector3 _u;
		Vector3 _v;
		Vector3 _w;
		double _lensRadius;
	};

}
