#pragma once

namespace raytracer
{
    class interval
    {
        public:
            float m_min, m_max;

            interval(): m_min(-INFTY), m_max(INFTY) {}
            interval(float min, float max): m_min(min), m_max(max) {}

            float size() const { return m_max - m_min; }
            bool contains(float x) const { return (x >= m_min && x <= m_max); }
            bool surrounds(float x) const { return (x > m_min && x < m_max); }

            static const interval empty, universe;

    };

    const interval interval::empty = interval(INFTY, -INFTY);
    const interval interval::universe = interval(-INFTY, INFTY);
}