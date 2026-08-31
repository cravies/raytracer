//
// Created by Ben_C on 8/31/2026.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "vec3.h"

class ray {
    point3 origin;
    vec3 direction;

    public:

        ray() = default;

        ray(const point3& _origin, const vec3& _direction) {
            origin = _origin;
            direction = _direction;
        }

        const point3 get_origin() const {
            return origin;
        }

        const vec3 get_direction() const {
            return direction;
        }

        point3 at(const double t) const {
            return origin + t * direction;
        }
};

#endif //RAYTRACER_RAY_H