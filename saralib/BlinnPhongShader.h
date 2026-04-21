#pragma once

#include "Shader.h"
#include "vec3.h"
#include "PointLight.h"

#include <vector>
#include <memory>

//This shader computes color based on the angle between the surface normal and light direction
class BlinnPhongShader : public Shader {
    public:
        vec3 rayColor(const HitStruct& hit,
            const ray &r,
            const std::vector<std::shared_ptr<PointLight>>& lights,
            const std::vector<std::shared_ptr<Shape>> &shapes,
            int depth) override;
        void setEyePosition(const vec3& pos) { eyePos = pos; }

    private:
        vec3 eyePos = vec3(0,0,0);
};