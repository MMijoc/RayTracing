#pragma once

#include "Ray.h"

namespace RayTracing
{
	class Camera {
	public:
		Camera(double verticalFieldOfView, double aspectRatio);

		Ray GetRay(double u, double v) const;

	private:
		Point3 _origin;
		Point3 _lowerLeftCorner;
		Vector3 _horizontal;
		Vector3 _vertical;
	};

}
