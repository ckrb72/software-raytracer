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
            float fuzz;

        public:
        metal(const glm::vec3& albedo, float fuzz): albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

        bool scatter(const ray& r_in, const hit_record& rec, glm::vec3& attenuation, ray& scattered) const override
        {
            glm::vec3 reflected = glm::reflect(r_in.direction(), rec.normal);
            reflected = glm::normalize(reflected) + (fuzz * random_unit_vector());
            scattered = ray(rec.point, reflected);
            attenuation = albedo;
            return glm::dot(scattered.direction(), rec.normal) > 0;
        }
    };

    class dielectric : public material
    {
        private:
            float refraction_index;

        public:

            dielectric(float refraction_index): refraction_index(refraction_index) {}

            bool scatter(const ray& r_in, const hit_record& rec, glm::vec3& attenuation, ray& scattered) const override
            {
                attenuation = glm::vec3(1.0, 1.0, 1.0);
                float ri = rec.front_face ? (1.0 / refraction_index) : refraction_index;
                glm::vec3 unit_direction = glm::normalize(r_in.direction());
                glm::vec3 refracted = glm::refract(unit_direction, rec.normal, ri);

                float cos_theta = std::fmin(glm::dot(-unit_direction, rec.normal), 1.0);
                float sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

                glm::vec3 direction;

                if(ri * sin_theta > 1.0)
                {
                    direction = glm::reflect(unit_direction, rec.normal);
                }
                else
                {
                    direction = glm::refract(unit_direction, rec.normal, ri);
                }

                scattered = ray(rec.point, direction);

                return true;
            }
    };

}