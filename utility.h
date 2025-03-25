#pragma once
#include <limits>
#include <cmath>
#include <iostream>
#include <memory>
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/vec3.hpp" // glm::vec3
#include "glm/gtx/norm.hpp"
#include "ray.h"

namespace raytracer
{
    const float INFTY = std::numeric_limits<float>::infinity();
    const float PI = 3.1415926535897932385;

    inline float degress_to_radians(float degrees) { return (degrees * PI) / 180.0;}
    inline float random_float() { return std::rand() / (RAND_MAX + 1.0); }
    inline float random_float(float min, float max) { return min + (max - min) * random_float(); }
    inline glm::vec3 random_vec() { return glm::vec3(random_float(), random_float(), random_float()); }
    inline glm::vec3 random_vec(float min, float max) { return glm::vec3(random_float(min, max), random_float(min, max), random_float(min, max)); }

    inline glm::vec3 random_unit_vector()
    {
        while(true)
        {
            glm::vec3 p = random_vec(-1, 1);
            float lensq = glm::length2(p);
            if(1e-160 < lensq && lensq <= 1)
            {
                p /= sqrt(lensq);
                return p;
            }
        }
    }

    inline glm::vec3 random_vec_on_hemisphere(const glm::vec3& normal)
    {
        glm::vec3 on_sphere = random_unit_vector();
        if(dot(on_sphere, normal) > 0.0) return on_sphere;
        else return -on_sphere;
    }

    // convert linear color to gamma color given a gamma factor (i.e. 2.2)
    inline float linear_to_gamma(float linear_component, float gamma)
    {
        if(linear_component > 0)
            return pow(linear_component, 1.0f / gamma);

        return 0;
    }

    inline bool vec_near_zero(const glm::vec3& vec) 
    {
        float s = 1e-8;
        return (std::fabs(vec.x) < s) && (std::fabs(vec.y) < s) && (std::fabs(vec.z) < s);
    }
}

#include "interval.h"