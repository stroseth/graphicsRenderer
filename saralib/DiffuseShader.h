#pragma once

#include "Shader.h"
#include "vec3.h"
#include "PointLight.h"
#include "Shape.h"

#include <vector>
#include <memory>

class DiffuseShader : public Shader {
    public:
        DiffuseShader() : diffuseReflectanceColor(vec3(0.0,0.0,0.0)) {}
        DiffuseShader(vec3 col) : diffuseReflectanceColor(col) {}
        vec3 rayColor(const HitStruct& h,
            const ray &r,
            const std::vector<std::shared_ptr<PointLight>>& lights,
            const std::vector<std::shared_ptr<Shape>> &shapes,
            int depth) override;
        void setDiffuseReflectanceColor(vec3 color){ diffuseReflectanceColor = color; }

    private:
        vec3 random_in_unit_sphere() const;
        vec3 diffuseReflectanceColor;
};