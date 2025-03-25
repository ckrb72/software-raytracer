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
}

#include "interval.h"