<<<<<<< HEAD
#include "color.h"
#include "vec3.h"
#include "ray.h"

#include <iostream>

color ray_color(const ray& r) {
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t * color(1.0, 1.0, 0.1);
=======
#include "rtweekend.h"

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

#include <iostream>

color ray_color(const ray& r, const hittable& world, int depth) {
    hit_record rec;

    if (depth<=0)
        return color(0, 0, 0);

    if (world.hit(r, 0.001, infinity, rec)) {
        //point3 target = rec.p + rec.normal + random_unit_vector();
        point3 target = rec.p + random_in_hemisphere(rec.normal);
        return 0.5 * ray_color(ray(rec.p, target - rec.p), world, depth-1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
>>>>>>> developing
}

int main() {

    // Image
<<<<<<< HEAD
    const auto aspect_ratio = 16/9;
    const int image_width = 400;
    const int image_height = image_width/aspect_ratio;

    //Camera
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3();
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);
=======
    const auto aspect_ratio = 16.0/9.0;
    const int image_width = 400;
    const int image_height = image_width/aspect_ratio;
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    std::cerr << image_height << std::endl;

    //World 
    hittable_list world;
    world.add(make_shared<sphere>(point3(-1, -1, -1), 0.9));
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(1, 0.1, -1), 0.1));
    world.add(make_shared<sphere>(point3(-1, 0.1, -1), 0.3));

    //Camera
    camera cam;
>>>>>>> developing

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
<<<<<<< HEAD
            auto u = double(i) / (image_width-1);
            auto v = double(j) / (image_height-1);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

=======
            color pixel_color(0, 0, 0);
            for(int s = 0; s < samples_per_pixel; ++s){
                auto u = (i+random_double()) / (image_width-1);
                auto v = (j+random_double()) / (image_height-1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }

    for (size_t i = 0; i < 100; i++)
    {
        std::cerr << random_double() << "\n";
    }
    

>>>>>>> developing
    std::cerr << "\nDone.\n";

}