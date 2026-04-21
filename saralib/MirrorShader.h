#pragma once

#include "Shader.h"
#include "vec3.h"
#include "PointLight.h"
#include "Shape.h"
#include "ray.h"

#include <vector>
#include <memory>

//This shader computes color based on the angle between the surface normal and light direction
class MirrorShader : public Shader {
    public:
        vec3 rayColor(const HitStruct& h,
            const ray &r,
            const std::vector<std::shared_ptr<PointLight>>& lights,
            const std::vector<std::shared_ptr<Shape>> &shapes,
            int depth) override;
};