#pragma once
#include "utility.h"

namespace raytracer
{

    struct hit_record
    {
        glm::vec3 point;
        glm::vec3 normal;
        float t;
        bool front_face;

        // Set face normal so it is always pointing against the ray direction
        void set_face_normal(const ray& r, const glm::vec3& outward_normal)
        {
            // if ray is in opposite direction of outward normal then you are on the front face
            front_face = glm::dot(r.direction(), outward_normal) < 0;

            // If on front face, use outward normal else use opposite direction
            normal = front_face ? outward_normal : -outward_normal;
        }
    };

    class hittable
    {
        public:
            virtual ~hittable() = default;
            virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
    };
}