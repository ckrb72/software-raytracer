#pragma once
#include "hittable.h"
#include "utility.h"
namespace raytracer
{
    class sphere : public hittable
    {
        private:
            glm::vec3 m_center;
            float m_radius;
            std::shared_ptr<material> mat;

        public:
            sphere(const glm::vec3& center, float radius) : m_center(center), m_radius(std::fmax(0, radius)) 
            {
                
            }

            bool hit(const ray& r, interval ray_t, hit_record& rec) const override
            {
                // Quadratic formula
                glm::vec3 oc = m_center - r.origin();
                float a = glm::length2(r.direction());
                float h = glm::dot(r.direction(), oc);
                float c = glm::length2(oc) - m_radius * m_radius;
                float discriminant = h*h - a*c;

                // If no real roots then no hit
                if (discriminant < 0) 
                    return false;

                // Find root within (ray_tmin, ray_tmax)
                float sqrtd = std::sqrt(discriminant);
                float root = (h - sqrtd) / a;
                if(!ray_t.surrounds(root))
                {
                    root = (h + sqrtd) / a;
                    if(!ray_t.surrounds(root))
                        // If no real roots within range (ray_tmin, ray_tmax) then no hit
                        return false;
                }

                rec.t = root;
                rec.point = r.at(root);
                glm::vec3 outward_normal = (rec.point - m_center) / m_radius;
                rec.set_face_normal(r, outward_normal);
                rec.mat = mat;

                return true;
            }
    };
}