#include "Ray.h"

namespace RayTracing {

    Ray::Ray() {}

    Ray::Ray(const Point3& origin, const Vector3& direction)
    {
        Origin = origin;
        Direction = direction;
    }


    Point3 Ray::GetOrigin() const
    {   
        return Origin;
    }

    Vector3 Ray::GetDirection() const
    {
        return Direction;
    }

    Point3 Ray::At(double t) const
    {
        return Origin + (t * Direction);
    }
}