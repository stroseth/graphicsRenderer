#pragma once

#include "Shader.h"
#include "HitStruct.h"
#include "vec3.h"
#include "PointLight.h"

#include <vector>
#include <memory>

class NormalShader : public Shader{
    public:
        vec3 rayColor(const HitStruct& hit, const std::vector<std::shared_ptr<PointLight>>& lights) override;
};