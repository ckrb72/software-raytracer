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
}

#include "interval.h"