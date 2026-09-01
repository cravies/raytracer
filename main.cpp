#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>

#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "sphere.h"
#include "tests.h"
#include <random>

static double pos_map(const double x) {
    return (x + 1.0) / 2.0;
}

static color ray_color(const ray& r) {
    const vec3 unit_ray = unit_vector(r.get_direction());
    const double y_normed = pos_map(unit_ray.y());
    return (1 - y_normed) * color(1.0, 1.0, 1.0) + y_normed*color(0.5, 0.7, 1.0);
}

static color surface_normal_color(const vec3 &surface_normal) {
    double r = pos_map(surface_normal.x());
    double g = pos_map(surface_normal.y());
    double b = pos_map(surface_normal.z());
    return {r, g, b};
}

struct hit_info {
    double t{};
    sphere hit_sphere;
};

static hit_info get_closest_hit(const vec3 &ray_direction, const vec3 &camera_origin, const std::vector<sphere>& spheres) {
    double closest_t = -1.0;
    sphere closest_sphere;
    for (auto& sphere: spheres) {
        double this_t = hit_sphere(ray_direction, camera_origin, sphere);
        if (this_t > 0 && closest_t == -1.0) {
            closest_t = this_t;
            closest_sphere = sphere;
        }
        else if (this_t > 0 && this_t < closest_t) {
            closest_t = this_t;
            closest_sphere = sphere;
        }
    }
    return {.t = closest_t, .hit_sphere = closest_sphere};
}

static double random_double(const double lower, const double upper) {
    // https://en.cppreference.com/cpp/numeric/random
    std::random_device r;
    std::default_random_engine re(r());
    std::uniform_real_distribution<double> unif(lower,upper);
    const double a_random_double = unif(re);
    return a_random_double;
}

int main() {
    std::ofstream out("test.ppm");

    int width = 400;
    double aspect = 16.0f / 9.0f;
    int height = ceil(static_cast<double>(width) / aspect);
    double viewport_height = 2.0;
    double viewport_width = viewport_height * (double(width) / height);

    out << "P3\n";
    out << width << " " << height << "\n";
    out << "255\n";

    // how much do we move to go 1 pixel down and to the right...
    double pixel_step_across = viewport_width / width;
    double pixel_step_down = -viewport_height / height;

    vec3 across_vec(pixel_step_across, 0.0f, 0.0f);
    vec3 down_vec(0.0f, pixel_step_down, 0.0f);

    vec3 camera_origin;
    vec3 center_viewport(0.0f, 0.0f, -1.0f);
    vec3 top_left_viewport = center_viewport - (width/2.0f) * across_vec - (height/2.0f) * down_vec;
    vec3 top_left_pixel = top_left_viewport + (0.5f * across_vec) + (0.5f * down_vec);

    constexpr int grid_size = 10;
    std::vector<sphere> spheres = make_scene(viewport_width, grid_size);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            vec3 pixel = top_left_pixel + (x * across_vec) + (y * down_vec);
            // for now, this is a no-op, but in future, we will change camera origin
            vec3 cam_to_pixel = pixel - camera_origin;
            if ((y % 100==0) && (x % 100==0)) {
                std::cout << x << "," << y << std::endl;
                std::cout << cam_to_pixel << std::endl;
            }
            ray pixel_ray(camera_origin, cam_to_pixel);
            vec3 ray_direction = pixel_ray.get_direction();
            color this_pixel;
            auto [t, hit_sphere] = get_closest_hit(ray_direction, camera_origin, spheres);
            if (t != -1.0) {
                // hit sphere - shade by normal
                // first build hit point
                vec3 hit_point = camera_origin + t * ray_direction;
                this_pixel = color(1.0, 0, 0);
                vec3 surface_normal = unit_vector(hit_point - hit_sphere.center);
                this_pixel = surface_normal_color(surface_normal);
            } else {
                // background blending
                this_pixel = color(ray_color(pixel_ray));
            }
            write_color(out, this_pixel);
        }
    }

    tests();
    return 0;
}
