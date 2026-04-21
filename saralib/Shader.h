#pragma once

#include "vec3.h"
#include "HitStruct.h"
#include "PointLight.h"
#include "ray.h"
#include "Shape.h"

#include <vector>
#include <memory>

// Abstract class.
//  * Description of materials associated w/ objects in the scene
class Shader{
    public:
        virtual vec3 rayColor(const HitStruct& hit,
            const ray &r,
            const std::vector<std::shared_ptr<PointLight>>& lights,
            const std::vector<std::shared_ptr<Shape>> &shapes,
            int depth) = 0;
};