#pragma once

#include "ray.h"
#include "vec3.h"
#include <memory>
#include <vector>

class Shape;
class PointLight;

vec3 computeRayColor(const ray &r,
    const std::vector<std::shared_ptr<Shape>> &shapes,
    const std::vector<std::shared_ptr<PointLight>> &lights,
    int depth );