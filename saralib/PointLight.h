#pragma once
#include "vec3.h"

// Basic PointLight class to store position, color, and intensity
class PointLight{
    public:
        PointLight() : position(vec3(0,10,5)), color(vec3(1,1,1)), intensity(1.0f) {}
        PointLight(const vec3& pos, const vec3& col, float intens = 1.0f)
            : position(pos), color(col), intensity(intens) {}

        vec3 getPosition() const { return position; }
        vec3 getColor() const { return color; }
        float getIntensity() const { return intensity; }

    private:
        vec3 position;
        vec3 color;
        float intensity = 1.0f;
};