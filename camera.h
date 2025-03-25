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

        glm::vec3 ray_color(const ray& r, int depth, const hittable& world) const
        {
            if (depth <= 0) return glm::vec3(0.0, 0.0, 0.0);

            hit_record rec;
            if(world.hit(r, interval(0.001, INFTY), rec))
            {
                // get a random vector on the hemisphere around the point we hit (defined by its normal)
                // essentially simulating a random reflection of the light off the object's surface
                //glm::vec3 direction = random_vec_on_hemisphere(rec.normal);
                
                // Lambertian diffuse (look into this more because i dont even know)
                glm::vec3 direction = rec.normal + random_unit_vector();

                // cast a ray in the direction of the random vector we just generated, returning half it's light value
                return 0.5f * ray_color(ray(rec.point, direction), depth - 1, world);

                // For normals: 
                // Convert [-1, 1] to [0, 1] so we can display it as a color
                //return 0.5f * (rec.normal + glm::vec3(1.0f, 1.0f, 1.0f));
            }
        
            glm::vec3 unit_direction = glm::normalize(r.direction());
            float a = 0.5f * (unit_direction.y + 1.0);
        
            return (1.0f - a) * glm::vec3(1.0, 1.0, 1.0) + a * glm::vec3(0.5, 0.7, 1.0);
        }

        void write_color(std::ostream& out, const glm::vec3& pixel_color)
        {
            float r = linear_to_gamma(pixel_color.r, 2.0);
            float g = linear_to_gamma(pixel_color.g, 2.0);
            float b = linear_to_gamma(pixel_color.b, 2.0);
        
            static interval intensity(0.0, 0.999);

            int rbyte = (int)(256 * intensity.clamp(r));
            int gbyte = (int)(256 * intensity.clamp(g));
            int bbyte = (int)(256 * intensity.clamp(b));
        
            out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
        }

        ray get_ray(int i, int j) const
        {
            glm::vec3 offset = sample_square();
            glm::vec3 pixel_sample = pixel00_loc + (((float)i + offset.x) * pixel_delta_u) + (((float)j + offset.y) * pixel_delta_v);
            glm::vec3 ray_origin = camera_center;
            glm::vec3 ray_direction = pixel_sample - ray_origin;
            return ray(ray_origin, ray_direction);
        }

        glm::vec3 sample_square() const
        {
            return glm::vec3(random_float() - 0.5f, random_float() - 0.5f, 0.0f);
        }


        public:

        double aspect_ratio = 1.0;
        int image_width = 100;
        int samples_per_pixel = 10;
        int max_depth = 10;

        void render(const hittable& world)
        {
            initialize();

            std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

            for (int j = 0; j < image_height; j++) {
                std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
                for (int i = 0; i < image_width; i++) {

                    glm::vec3 pixel_color = glm::vec3(0.0f, 0.0f, 0.0f);
                    for(int sample = 0; sample < samples_per_pixel; sample++)
                    {
                        ray r = get_ray(i, j);
                        pixel_color += ray_color(r, max_depth, world);
                    }

                    pixel_color /= (float)samples_per_pixel;
                    write_color(std::cout, pixel_color);
                }
            }
            std::clog << "\rDone.                       \n";
        }
    };
}