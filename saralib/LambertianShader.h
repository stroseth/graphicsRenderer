#pragma once

#include "Shader.h"
#include "vec3.h"

class LambertianShader : public Shader {
    public:
        vec3 rayColor(const HitStructure& h) override;
};