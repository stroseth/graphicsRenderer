#include "Triangle.h"

bool Triangle::intersect(const ray& r, float t_min, float& t_max, HitStruct& hit) const override{
    //needs implementation

    return false;
}

vec3 Triangle::getColor() const override{
    return color;
}