//
// Created by Ben_C on 8/31/2026.
//

#ifndef RAYTRACER_VEC3_H
#define RAYTRACER_VEC3_H

#include <cmath>
#include <ostream>

class vec3 {

    public:
        double e[3]{};

        vec3 () {
            e[0] = e[1] = e[2] = 0.0f;
        }

        vec3 (const double x, const double y, const double z) {
            e[0] = x;
            e[1] = y;
            e[2] = z;
        }

        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        double length_squared() const {
            return pow(e[0], 2.0f) + pow(e[1], 2.0f) + pow(e[2], 2.0f);
        }

        double length() const {
            return sqrt(length_squared());
        }

};

inline std::ostream& operator<<(std::ostream& out, const vec3 &v){
    out << v.x() << " " << v.y() << " " << v.z();
    return out;
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
    const vec3 result = {u.e[0]+v.e[0], u.e[1]+v.e[1], u.e[2]+v.e[2]};
    return result;
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
    const vec3 result = {u.e[0]-v.e[0], u.e[1]-v.e[1], u.e[2]-v.e[2]};
    return result;
}

inline vec3 operator*(const double t, const vec3 &v) {
    const vec3 result = {v.e[0] * t, v.e[1] * t, v.e[2] * t};
    return result;
}

inline vec3 operator/(const vec3 &v, const double t) {
    const vec3 result = {v.e[0] / t, v.e[1] / t, v.e[2] / t};
    return result;
}

inline vec3 unit_vector(const vec3 &v) {
    auto v_norm = v.length();
    return v / v_norm;
}

inline double dot(const vec3 &u, const vec3 &v) {
    return u.x()*v.x() + u.y()*v.y() + u.z()*v.z();
}

using point3=vec3;

#endif //RAYTRACER_VEC3_H
