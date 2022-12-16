#pragma once

#include "Vector3.h"

namespace RayTracing {
    class Ray {
    public:
        Point3 Origin;
        Vector3 Direction;

        Ray();
        Ray(const Point3& origin, const Vector3& direction);


        Point3 GetOrigin() const;
        Vector3 GetDirection() const;
        Point3 At(double t) const;
    };
}
