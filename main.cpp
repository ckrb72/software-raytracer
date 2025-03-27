#include "utility.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

int main() {

    // World
    raytracer::hittable_list world;

    std::shared_ptr<raytracer::material> material_ground = std::make_shared<raytracer::lambertian>(glm::vec3(0.8, 0.8, 0.0));
    std::shared_ptr<raytracer::material> material_center = std::make_shared<raytracer::lambertian>(glm::vec3(0.1, 0.2, 0.5));
    std::shared_ptr<raytracer::material> material_left = std::make_shared<raytracer::dielectric>(1.5f);
    std::shared_ptr<raytracer::material> material_bubble = std::make_shared<raytracer::dielectric>(1.0f / 1.5f);
    std::shared_ptr<raytracer::material> material_right = std::make_shared<raytracer::metal>(glm::vec3(0.8, 0.6, 0.2), 1.0); 

    world.add(std::make_shared<raytracer::sphere>(glm::vec3(0.0, 0.0, -1.2), 0.5, material_center));
    world.add(std::make_shared<raytracer::sphere>(glm::vec3(0.0, -100.5, -1.0), 100, material_ground));
    world.add(std::make_shared<raytracer::sphere>(glm::vec3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.add(std::make_shared<raytracer::sphere>(glm::vec3(-1.0, 0.0, -1.0), 0.4, material_bubble));
    world.add(std::make_shared<raytracer::sphere>(glm::vec3(1.0, 0.0, -1.0), 0.5, material_right));

    raytracer::camera camera;
    camera.aspect_ratio = 16.0 / 9.0;
    camera.image_width = 400;
    camera.samples_per_pixel = 100;
    camera.max_depth = 50;
    camera.vfov = 90.0f;

    // Render
    camera.render(world);
}