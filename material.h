#pragma once
#include "hittable.h"

namespace raytracer
{
    class material
    {
        public:
            virtual ~material() = default;
            virtual bool scatter(const ray& r_in, const hit_record& rec, glm::vec3& attenuation, ray& scattered) const { return false; }
    };

    class lambertian : public material
    {
        private:
            glm::vec3 albedo;

        public:
            lambertian(const glm::vec3& albedo): albedo(albedo) {}

            bool scatter(const ray& r_in, const hit_record& rec, glm::vec3& attenuation, ray& scattered) const override
            {
                glm::vec3 scatter_direction = rec.normal + random_unit_vector();

                if(vec_near_zero(scatter_direction)) scatter_direction = rec.normal;

                scattered = ray(rec.point, scatter_direction);
                attenuation = albedo;
                return true;
            }
    };


    class metal : public material
    {
        private:
            glm::vec3 albedo;

        public:
        metal(const glm::vec3& albedo): albedo(albedo) {}

        bool scatter(const ray& r_in, const hit_record& rec, glm::vec3& attenuation, ray& scattered) const override
        {
            glm::vec3 reflected = glm::reflect(r_in.direction(), rec.normal);
            scattered = ray(rec.point, reflected);
            attenuation = albedo;
            return true;
        }

    };
}