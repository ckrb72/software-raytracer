#include "utility.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

int main() {

    // World
    raytracer::hittable_list world;

    std::shared_ptr<raytracer::material> material_ground = std::make_shared<raytracer::lambertian>(glm::vec3(0.5, 0.5, 0.5));
    world.add(std::make_shared<raytracer::sphere>(glm::vec3(0.0, -1000.0, 0.0), 1000.0, material_ground));

    for(int i = -11; i < 11; i++)
    {
        for(int j = -11; j < 11; j++)
        {
            float choose_mat = raytracer::random_float();
            glm::vec3 center = glm::vec3(i + 0.9 * raytracer::random_float(), 0.2, j + 0.9 * raytracer::random_float());

            if(glm::length(center - glm::vec3(4.0, 0.2, 0.0)) > 0.9)
            {
                std::shared_ptr<raytracer::material> sphere_material;

                if(choose_mat < 0.8)
                {
                    glm::vec3 albedo = raytracer::random_unit_vector() * raytracer::random_unit_vector();
                    sphere_material = std::make_shared<raytracer::lambertian>(albedo);
                    world.add(std::make_shared<raytracer::sphere>(center, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95)
                {
                    glm::vec3 albedo = raytracer::random_unit_vector();
                    float fuzz = raytracer::random_float(0.0, 0.5);
                    sphere_material = std::make_shared<raytracer::metal>(albedo, fuzz);
                    world.add(std::make_shared<raytracer::sphere>(center, 0.2, sphere_material));
                }
                else
                {
                    sphere_material = std::make_shared<raytracer::dielectric>(1.5f);
                    world.add(std::make_shared<raytracer::sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }


    std::shared_ptr<raytracer::material> material1 = std::make_shared<raytracer::dielectric>(1.5);
    world.add(std::make_shared<raytracer::sphere>(glm::vec3(0.0, 1.0, 0.0), 1.0, material1));

    std::shared_ptr<raytracer::material> material2 = std::make_shared<raytracer::lambertian>(glm::vec3(0.4, 0.2, 0.1));
    world.add(std::make_shared<raytracer::sphere>(glm::vec3(-4.0, 1.0, 0.0), 1.0, material2));

    std::shared_ptr<raytracer::material> material3 = std::make_shared<raytracer::metal>(glm::vec3(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<raytracer::sphere>(glm::vec3(4.0, 1.0, 0.0), 1.0, material3));

    /*std::shared_ptr<raytracer::material> material_ground = std::make_shared<raytracer::lambertian>(glm::vec3(0.8, 0.8, 0.0));
    std::shared_ptr<raytracer::material> material_center = std::make_shared<raytracer::lambertian>(glm::vec3(0.1, 0.2, 0.5));
    std::shared_ptr<raytracer::material> material_left = std::make_shared<raytracer::dielectric>(1.5f);
    std::shared_ptr<raytracer::material> material_bubble = std::make_shared<raytracer::dielectric>(1.0f / 1.5f);
    std::shared_ptr<raytracer::material> material_right = std::make_shared<raytracer::metal>(glm::vec3(0.8, 0.6, 0.2), 1.0); 

    world.add(std::make_shared<raytracer::sphere>(glm::vec3(0.0, 0.0, -1.2), 0.5, material_center));
    world.add(std::make_shared<raytracer::sphere>(glm::vec3(0.0, -100.5, -1.0), 100, material_ground));
    world.add(std::make_shared<raytracer::sphere>(glm::vec3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.add(std::make_shared<raytracer::sphere>(glm::vec3(-1.0, 0.0, -1.0), 0.4, material_bubble));
    world.add(std::make_shared<raytracer::sphere>(glm::vec3(1.0, 0.0, -1.0), 0.5, material_right));*/

    raytracer::camera camera;
    camera.aspect_ratio = 16.0 / 9.0;
    camera.image_width = 400;
    camera.samples_per_pixel = 500;
    camera.max_depth = 50;
    camera.vfov = 20.0f;
    camera.look_from = glm::vec3(13.0f, 2.0f, 3.0f);
    camera.look_at = glm::vec3(0.0f, 0.0f, 0.0f);
    camera.vup = glm::vec3(0.0f, 1.0f, 0.0f);
    camera.defocus_angle = 0.6f;
    camera.focus_dist = 10.0;

    // Render
    camera.render(world);
}