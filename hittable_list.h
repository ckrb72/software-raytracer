#pragma once
#include "hittable.h"
#include "utility.h"
#include <vector>


namespace raytracer
{
    class hittable_list : public hittable
    {
        public:
            std::vector<std::shared_ptr<hittable>> objects;
            hittable_list() {}
            hittable_list(std::shared_ptr<hittable> object) { add(object); }
            void clear() { objects.clear(); }
            void add(std::shared_ptr<hittable> object) { objects.push_back(object); }

            bool hit(const ray& r, float ray_tmin, float ray_tmax, hit_record& rec) const override
            {
                hit_record temp_rec;
                bool hit_anything = false;
                float closest_so_far = ray_tmax;

                for(const std::shared_ptr<hittable>& object : objects)
                {
                    if(object->hit(r, ray_tmin, closest_so_far, temp_rec))
                    {
                        hit_anything = true;
                        closest_so_far = temp_rec.t;
                        rec = temp_rec;
                    }
                }

                return hit_anything;
            }
    };
}