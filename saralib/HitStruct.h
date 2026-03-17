#pragma once

#include "vec3.h"

class Shape;

struct HitStruct{
    float t;
    vec3 point;
    vec3 normal; //stores surface normal
    const Shape* shape = nullptr;
};