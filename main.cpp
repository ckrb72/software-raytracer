#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/vec3.hpp" // glm::vec3
#include "glm/vec4.hpp" // glm::vec4
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/ext/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale
#include "glm/gtx/norm.hpp"
#include "ray.h"

void write_color(std::ostream& out, const glm::vec3& pixel_color);
glm::vec3 ray_color(const raytracer::ray& r);

int main() {

    // Image
    float aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    int image_height = (int)(image_width  / aspect_ratio);
    image_height = image_height < 1.0 ? 1.0 : image_height;

    float focal_length = 1.0;
    float viewport_height = 2.0;
    float viewport_width = viewport_height * ((float)image_width / (float)image_height);
    glm::vec3 camera_center = glm::vec3(0.0, 0.0, 0.0);

    glm::vec3 viewport_u = glm::vec3(viewport_width, 0.0, 0.0);
    glm::vec3 viewport_v = glm::vec3(0.0, -viewport_height, 0.0);

    glm::vec3 pixel_delta_u = viewport_u / (float)image_width;
    glm::vec3 pixel_delta_v = viewport_v / (float)image_height;

    glm::vec3 viewport_upper_left = camera_center - glm::vec3(0.0, 0.0, focal_length) - viewport_u / 2.0f - viewport_v / 2.0f;
    glm::vec3 pixel00_loc = viewport_upper_left + 0.5f * (pixel_delta_u + pixel_delta_v);


    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            glm::vec3 pixel_center = pixel00_loc + ((float)i * pixel_delta_u) + ((float)j * pixel_delta_v);
            glm::vec3 ray_direction = pixel_center - camera_center;
            raytracer::ray r(camera_center, ray_direction);
    

            write_color(std::cout, ray_color(r));
        }
    }
    std::clog << "\rDone.                       \n";
}

void write_color(std::ostream& out, const glm::vec3& pixel_color)
{
    float r = pixel_color.r;
    float g = pixel_color.g;
    float b = pixel_color.b;

    int rbyte = (int)(255.999 * r);
    int gbyte = (int)(255.999 * g);
    int bbyte = (int)(255.999 * b);

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

float hit_sphere(const glm::vec3& center, float radius, const raytracer::ray& r)
{
    glm::vec3 oc = center - r.origin();
    float a = glm::length2(r.direction());
    float h = glm::dot(r.direction(), oc);
    float c = glm::length2(oc) - radius * radius;
    float discriminant = h*h - a*c;
    if (discriminant < 0)
    {
        return -1.0;
    }
    else
    {
        // return the root of the quadratic formula
        return (h - std::sqrt(discriminant)) / a;
    }
}

glm::vec3 ray_color(const raytracer::ray& r)
{
    glm::vec3 sphere_center = glm::vec3(0.0, 0.0, -1.0);
    float t = hit_sphere(sphere_center, 0.5, r);
    if (t > 0.0)
    {
        // get normal (position the ray hits minus position of the sphere center)
        glm::vec3 n = glm::normalize(r.at(t) - sphere_center);

        // Convert from [-1, 1] to [0, 1]
        return 0.5f * glm::vec3(n.x + 1.0f, n.y + 1.0f, n.z + 1.0f);
    }

    glm::vec3 unit_direction = glm::normalize(r.direction());
    float a = 0.5f * (unit_direction.y + 1.0);

    return (1.0f - a) * glm::vec3(1.0, 1.0, 1.0) + a * glm::vec3(0.5, 0.7, 1.0);
}
