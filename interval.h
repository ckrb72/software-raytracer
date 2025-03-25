#pragma once

namespace raytracer
{
    class interval
    {
        public:
            float min, max;

            interval(): min(-INFTY), max(INFTY) {}
            interval(float min, float max): min(min), max(max) {}

            float size() const { return max - min; }
            bool contains(float x) const { return (x >= min && x <= max); }
            bool surrounds(float x) const { return (x > min && x < max); }

            static const interval empty, universe;

    };

    const interval interval::empty = interval(INFTY, -INFTY);
    const interval interval::universe = interval(-INFTY, INFTY);
}