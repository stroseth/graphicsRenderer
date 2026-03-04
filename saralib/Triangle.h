#pragma once

#include "vec3.h"
#include "Shape.h"

class Triangle : public Shape{
    public:
        Triangle() : vertex_a(vec3(0,0,0)), vertex_b(vec3(1,0,0)), vertex_c(vec3(0,1,0)), color(vec3(1.0,1.0,1.0)) {}
        Triangle(point3 u, point3 v, point3 w) : vertex_a(u), vertex_b(v), vertex_c(w), color(vec3(1.0,1.0,1.0)) {}
        Triangle(point3 u, point3 v, point3 w, color c) : vertex_a(u), vertex_b(v), vertex_c(w), color(c) {}

        bool intersect(const ray& r, float t_min, float& t_max, HitStruct& hit) const override{}
        vec3 getColor() const override{}

    private:
        point3 vertex_a, vertex_b, vertex_c;

        vec3 color;
}