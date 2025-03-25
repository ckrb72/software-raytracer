#pragma once
#include "glm/vec3.hpp"

namespace raytracer
{
    class ray
    {
        private:
            glm::vec3 m_dir;
            glm::vec3 m_origin;

        public:

            ray() {}
            ray(const glm::vec3& origin, const glm::vec3& direction) : m_origin(origin), m_dir(direction) {}

            const glm::vec3& origin() const { return m_origin; }
            const glm::vec3& direction() const { return m_dir; }

            glm::vec3 at(float t) const
            {
                return m_origin + t * m_dir;
            }
    };
}