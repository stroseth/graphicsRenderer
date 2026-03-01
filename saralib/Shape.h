#pragma once

#include "HitStruct.h"
#include "ray.h"
#include "vec3.h"

//Base class for things like da spheres and allat
//Has the shader information in it.
class Shape{
public:
    virtual bool intersect(const ray& r, float t_min, float& t_max, HitStruct& hit) const = 0;
    virtual getColor() const = 0;
};