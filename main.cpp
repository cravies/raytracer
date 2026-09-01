#include <fstream>
#include <iostream>
#include <cmath>

#include "vec3.h"
#include "color.h"
#include "ray.h"

static color ray_color(const ray& r) {
    const vec3 unit_ray = unit_vector(r.get_direction());
    const double y_normed = (unit_ray.y() + 1.0) / 2.0;
    return (1 - y_normed) * color(1.0, 1.0, 1.0) + y_normed*color(0.5, 0.7, 1.0);
}

bool hit_sphere(const vec3 &ray_direction, const vec3 &origin, const vec3 &sphere_center, double radius) {
    vec3 to_sphere = sphere_center - origin;
    double a = dot(ray_direction, ray_direction);
    double b = -2.0 * dot(ray_direction, to_sphere);
    double c = dot(sphere_center, sphere_center) - pow(radius, 2.0f);
    // check if b^2 - 4ac is 0 or positive - implies real solutions
    if ((b*b - 4*a*c)<0) {
        return false;
    }
    return true;
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

    vec3 sphere_center(0, 0, -1);
    double sphere_radius = 0.5;
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
            if (hit_sphere(ray_direction, camera_origin, sphere_center, sphere_radius)) {
                // hit sphere - aka flat colour
                this_pixel = color(1.0, 0, 0);
            } else {
                // background blending
                this_pixel = color(ray_color(pixel_ray));
            }
            write_color(out, this_pixel);
        }
    }

    std::cout << dot(vec3(1,0,0), vec3(0,1,0)) << '\n';    // 0
    std::cout << dot(vec3(1,2,3), vec3(4,5,6)) << '\n';    // 32
    std::cout << dot(vec3(1,2,3), vec3(1,2,3)) << '\n';    // 14, matches length_squared
    std::cout << dot(vec3(2,3,4), vec3(-1,2,-1)) << '\n';  // 0, orthogonal
    std::cout << dot(vec3(1,1,0), vec3(-1,-1,0)) << '\n';  // -2, anti-aligned

    std::cout << "height " << height << '\n';               // 225
    std::cout << "vp_width " << viewport_width << '\n';     // 3.55556
    std::cout << "across " << across_vec << '\n';           // 0.00888889 0 0
    std::cout << "down " << down_vec << '\n';               // 0 -0.00888889 0
    std::cout << "top_left_corner " << top_left_viewport << '\n';  // -1.77778 1 -1
    std::cout << "top_left_pixel " << top_left_pixel << '\n';

    std::cout << ray(point3(0,0,0), vec3(1,2,3)).at(2.0) << '\n';
    std::cout << ray(point3(1,1,1), vec3(0,0,-1)).at(0.5) << '\n';
    std::cout << ray(point3(1,1,1), vec3(0,0,-1)).at(0.0) << '\n';

    std::cout << vec3(3,4,0).length() << '\n';                    // 5
    std::cout << vec3(1,2,3).length_squared() << '\n';            // 14
    std::cout << vec3(5,7,9) - vec3(1,2,3) << '\n';               // 4 5 6
    std::cout << vec3(2,4,8) / 2.0 << '\n';                       // 1 2 4
    std::cout << unit_vector(vec3(0,3,0)) << '\n';                // 0 1 0
    std::cout << unit_vector(vec3(1,1,1)).length() << '\n';       // 1
    std::cout << unit_vector(vec3(-2,0,0)) << '\n';               // -1 0 0
    return 0;
}