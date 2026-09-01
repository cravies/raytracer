//
// Created by Ben_C on 9/1/2026.
//

#include "tests.h"
#include "ray.h"
#include "vec3.h"
#include <iostream>
#include <cassert>

static bool near(double a, double b) {
    return std::fabs(a - b) < 1e-9;
}

static bool vec_near(const vec3& u, const vec3& v) {
    return near(u.x(), v.x()) && near(u.y(), v.y()) && near(u.z(), v.z());
}

void tests() {
    assert(near(dot(vec3(1,0,0), vec3(0,1,0)), 0.0));
    assert(near(dot(vec3(1,2,3), vec3(4,5,6)), 32.0));
    assert(near(dot(vec3(1,2,3), vec3(1,2,3)), 14.0));
    assert(near(dot(vec3(2,3,4), vec3(-1,2,-1)), 0.0));
    assert(near(dot(vec3(1,1,0), vec3(-1,-1,0)), -2.0));

    assert(vec_near(ray(point3(0,0,0), vec3(1,2,3)).at(2.0), vec3(2,4,6)));
    assert(vec_near(ray(point3(1,1,1), vec3(0,0,-1)).at(0.5), vec3(1,1,0.5)));
    assert(vec_near(ray(point3(1,1,1), vec3(0,0,-1)).at(0.0), vec3(1,1,1)));

    assert(near(vec3(3,4,0).length(), 5.0));
    assert(near(vec3(1,2,3).length_squared(), 14.0));
    assert(vec_near(vec3(5,7,9) - vec3(1,2,3), vec3(4,5,6)));
    assert(vec_near(vec3(2,4,8) / 2.0, vec3(1,2,4)));
    assert(vec_near(unit_vector(vec3(0,3,0)), vec3(0,1,0)));
    assert(near(unit_vector(vec3(1,1,1)).length(), 1.0));
    assert(vec_near(unit_vector(vec3(-2,0,0)), vec3(-1,0,0)));

    std::cout << "all tests passed\n";
}