// Abstract class.
//  * Description of materials associated w/ objects in the scene

#pragma once

#include "vec3.h"
#include "HitStruct.h"

class Shader{
    public:
        virtual vec3 rayColor(const HitStructure &h) = 0;
};