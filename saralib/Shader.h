// Abstract class.
//  * Description of materials associated w/ objects in the scene

#pragma once

#include "vec3.h"
#include "HitStruct.h"
#include "PointLight.h"

#include <vector>
#include <memory>

class Shader{
    public:
        virtual vec3 rayColor(const HitStruct& hit, const std::vector<std::shared_ptr<PointLight>>& lights) = 0;
};