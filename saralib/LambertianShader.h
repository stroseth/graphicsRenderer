#pragma once

#include "Shader.h"
#include "vec3.h"
#include "PointLight.h"

#include <vector>
#include <memory>

//This shader computes color based on the angle between the surface normal and light direction
class LambertianShader : public Shader {
    public:
        vec3 rayColor(const HitStructure& h, const std::vector<std::shared_ptr<PointLight>>& lights) override;
};