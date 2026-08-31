//
// Created by Ben_C on 8/31/2026.
//

#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H

#include <fstream>
#include "vec3.h"

using color=vec3;

inline int write_color(std::ofstream& out, color& pixel_color) {
    int r = static_cast<int>(pixel_color.x() * 255.999);
    int g = static_cast<int>(pixel_color.y() * 255.999);
    int b = static_cast<int>(pixel_color.z() * 255.999);
    out << r << " " << g << " " << b << "\n";
    return 0;
}

#endif //RAYTRACER_COLOR_H
