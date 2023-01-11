#pragma once

#include "Hittable.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

namespace RayTracing {
    class HittableList : public Hittable {
    public:
		HittableList() = default;
    	HittableList(shared_ptr<Hittable> object) { Add(object); }

        void Clear() { Objects.clear(); }
        void Add(shared_ptr<Hittable> object) { Objects.push_back(object); }

        virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override;

    public:
        std::vector<shared_ptr<Hittable>> Objects;
    };

    inline bool HittableList::Hit(const Ray& ray, const double tMin, double const tMax, HitRecord& record) const {
        HitRecord tempRecord;
        bool hitAnything = false;
        auto closestSoFar = tMax;

        for (const auto& object : Objects) {
            if (object->Hit(ray, tMin, closestSoFar, tempRecord)) {
                hitAnything = true;
                closestSoFar = tempRecord.t;
                record = tempRecord;
            }
        }

        return hitAnything;
    }
}
