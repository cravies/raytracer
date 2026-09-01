cmake_minimum_required(VERSION 4.3)
project(raytracer)

set(CMAKE_CXX_STANDARD 20)

add_executable(raytracer main.cpp
        vec3.h
        color.h
        ray.h
        sphere.h
        tests.cpp
        tests.h
)
