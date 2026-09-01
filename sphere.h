//
// Created by Ben_C on 9/1/2026.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

struct sphere {
    vec3 center;
    double radius{};
};

inline double hit_sphere(const vec3 &ray_direction, const vec3 &origin, const sphere& sphere) {
    // quadratic equation = (-b +- sqrt(b^2 - 4ac))/2a
    vec3 to_sphere = sphere.center - origin;
    double a = dot(ray_direction, ray_direction);
    double b = -2.0 * dot(ray_direction, to_sphere);
    double c = dot(sphere.center, sphere.center) - pow(sphere.radius, 2.0f);
    // check if b^2 - 4ac is 0 or positive - implies real solutions
    // otherwise we get nasty imaginary numbers and we cooked
    double sqrt_guy = (b*b - 4*a*c);
    if (sqrt_guy < 0) {
        // dummy return - no solution
        return -1.0;
    }
    double t_plus = (-b + sqrt(sqrt_guy)) / (2*a);
    double t_minus = (-b - sqrt(sqrt_guy)) / (2*a);
    if (t_plus<0 && t_minus<0) {
        // both hits to the sphere lay "behind the camera"
        // so we don't have an invalid (positive) in front of camera t hit
        return -1.0;
    }
    // we want the "closer solution" i.e the front of the sphere (smaller t)
    // as remember t is the distance along the ray we've travelled...
    if (t_plus > 0 && t_minus < 0) {
        // only t_plus valid
        return t_plus;
    } else if (t_minus > 0 && t_plus < 0) {
        // only t_minus valid
        return t_minus;
    }
    // both valid, return smaller one
    if (t_plus < t_minus) {
        return t_plus;
    }
    return t_minus;
}

#endif //RAYTRACER_SPHERE_H
