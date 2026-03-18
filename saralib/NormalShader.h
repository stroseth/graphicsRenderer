#pragma once

#include "Shader.h"
#include "HitStruct.h"
#include "vec3.h"

class NormalShader : public Shader{
    public:
        vec3 rayColor(const HitStruct& hit) override;
};