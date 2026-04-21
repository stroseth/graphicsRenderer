#pragma once

#include "Shape.h"
#include "vec3.h"
#include <memory>

class Shader;

class Sphere : public Shape
{
    public:
        //constructors obvs
        Sphere(): center(vec3(0,0,0)), radius(1.0), color(vec3(1.0,1.0,1.0)) {}
        Sphere(vec3 c, float r): center(c), radius(r), color(vec3(1.0,1.0,1.0)) {}
        Sphere(vec3 c, float r, vec3 col): center(c), radius(r), color(col){}
        Sphere(vec3 c, float r, vec3 col, std::shared_ptr<Shader> shd) : center(c), radius(r), color(col), shader(shd) {}

        bool intersect(const ray&r, float t_min, float& t_max, HitStruct& hit) const override;
        vec3 getColor() const override;

        //getters
        float getRadius() const;
        point3 getCenter() const;
        std::shared_ptr<Shader> getShader() const override;

        //shader setter
        void setShader(std::shared_ptr<Shader> shd);

    private:
        point3 center;
        float radius;
        vec3 color;
        std::shared_ptr<Shader> shader = nullptr;
};