//
// Created by Ben_C on 9/1/2026.
//

#include "tests.h"
#include "ray.h"
#include "vec3.h"
#include <iostream>
#include <cassert>
#include "sphere.h"

static bool near(double a, double b) {
    return std::fabs(a - b) < 1e-9;
}

static bool vec_near(const vec3& u, const vec3& v) {
    return near(u.x(), v.x()) && near(u.y(), v.y()) && near(u.z(), v.z());
}

static void test_make_scene() {
    auto scene = make_scene(3.55556, 4);

    assert(scene.size() == 17);  // 1 globe + 4x4 grid

    // globe is first, huge, below the plane
    assert(near(scene[0].radius, 100.0));
    assert(scene[0].center.y() < -99.0);

    // all grid balls share one radius and a common height below eye level
    const double ball_y = scene[1].center.y();
    const double ball_r = scene[1].radius;
    assert(ball_y < 0.0);
    assert(ball_r > 0.0 && ball_r < 1.0);
    for (size_t i = 1; i < scene.size(); i++) {
        assert(near(scene[i].radius, ball_r));
        assert(near(scene[i].center.y(), ball_y));
    }

    // balls rest on the globe: globe top == ball bottom
    double globe_top = scene[0].center.y() + scene[0].radius;
    assert(near(globe_top, ball_y - scene[1].radius));

    // grid is grid_size^2 distinct positions
    for (size_t i = 1; i < scene.size(); i++)
        for (size_t j = i + 1; j < scene.size(); j++)
            assert(!vec_near(scene[i].center, scene[j].center));

    // x spacing between adjacent balls in a row is viewport_width / grid_size
    assert(near(scene[2].center.x() - scene[1].center.x(), 0.0) ||
           near(scene[2].center.z() - scene[1].center.z(), 1.0 / 4));

    // every ball lies within the viewport's x extent
    for (size_t i = 1; i < scene.size(); i++)
        assert(std::fabs(scene[i].center.x()) <= 3.55556 / 2 + 0.15);

    std::cout << "make_scene tests passed\n";
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

    test_make_scene();

    std::cout << "all tests passed\n";
}