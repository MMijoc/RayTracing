#pragma once

#include "Ray.h"

namespace RayTracing
{
	class Camera {
	public:
		Camera(Point3 lookFrom, Point3 lookAt, Point3 viewUp, double verticalFieldOfView, double aspectRatio);

		Ray GetRay(double s, double t) const;

	private:
		Point3 _origin;
		Point3 _lowerLeftCorner;
		Vector3 _horizontal;
		Vector3 _vertical;
	};

}
