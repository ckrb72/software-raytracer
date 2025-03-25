#include "utility.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

int main() {

    // World
    raytracer::hittable_list world;
    world.add(std::make_shared<raytracer::sphere>(glm::vec3(0.0, 0.0, -1.0), 0.5));
    world.add(std::make_shared<raytracer::sphere>(glm::vec3(0.0, -100.5, -1.0), 100));

    raytracer::camera camera;
    camera.aspect_ratio = 16.0 / 9.0;
    camera.image_width = 400;
    camera.samples_per_pixel = 100;
    camera.max_depth = 50;

    // Render
    camera.render(world);
}