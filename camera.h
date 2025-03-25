#pragma once
#include "hittable.h"
#include "utility.h"

namespace raytracer
{
    class camera
    {
        private:
        int image_height;
        glm::vec3 camera_center;
        glm::vec3 pixel00_loc;
        glm::vec3 pixel_delta_u;
        glm::vec3 pixel_delta_v;

        void initialize()
        {
            image_height = (int)(image_width  / aspect_ratio);
            image_height = image_height < 1.0 ? 1.0 : image_height;

            camera_center = glm::vec3(0.0, 0.0, 0.0);
        
            float focal_length = 1.0;
            float viewport_height = 2.0;
            float viewport_width = viewport_height * ((float)image_width / (float)image_height);
        
            glm::vec3 viewport_u = glm::vec3(viewport_width, 0.0, 0.0);
            glm::vec3 viewport_v = glm::vec3(0.0, -viewport_height, 0.0);
        
            pixel_delta_u = viewport_u / (float)image_width;
            pixel_delta_v = viewport_v / (float)image_height;
        
            glm::vec3 viewport_upper_left = camera_center - glm::vec3(0.0, 0.0, focal_length) - viewport_u / 2.0f - viewport_v / 2.0f;
            pixel00_loc = viewport_upper_left + 0.5f * (pixel_delta_u + pixel_delta_v);
        }

        glm::vec3 ray_color(const ray& r, const hittable& world) const
        {
            raytracer::hit_record rec;
            if(world.hit(r, raytracer::interval(0, raytracer::INFTY), rec))
            {
                // Convert [-1, 1] to [0, 1] so we can display it as a color
                return 0.5f * (rec.normal + glm::vec3(1.0f, 1.0f, 1.0f));
            }
        
            glm::vec3 unit_direction = glm::normalize(r.direction());
            float a = 0.5f * (unit_direction.y + 1.0);
        
            return (1.0f - a) * glm::vec3(1.0, 1.0, 1.0) + a * glm::vec3(0.5, 0.7, 1.0);
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


        public:

        double aspect_ratio = 1.0;
        int image_width = 100;

        void render(const hittable& world)
        {
            initialize();

            std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

            for (int j = 0; j < image_height; j++) {
                std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
                for (int i = 0; i < image_width; i++) {
                    glm::vec3 pixel_center = pixel00_loc + ((float)i * pixel_delta_u) + ((float)j * pixel_delta_v);
                    glm::vec3 ray_direction = pixel_center - camera_center;
                    raytracer::ray r(camera_center, ray_direction);
            
                    glm::vec3 pixel_color = ray_color(r, world);
                    write_color(std::cout, pixel_color);
                }
            }
            std::clog << "\rDone.                       \n";
        }
    };
}