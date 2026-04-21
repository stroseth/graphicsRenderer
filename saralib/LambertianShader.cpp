#include "LambertianShader.h"
#include "Shape.h"

//  Computes color based on the angle between the surface normal and light direction
vec3 LambertianShader::rayColor(const HitStruct& h, const std::vector<std::shared_ptr<PointLight>>& lights){
    
    vec3 materialColor = h.shape->getColor();
    vec3 color(0.0, 0.0, 0.0);

    for (const auto& light : lights){
        vec3 lightDir = unit_vector(light->getPosition() - h.point); // Compute the light direction from the hit point toward the light
        float diff = std::max(dot(h.normal, lightDir), 0.0f); // Calculate the diffuse coefficient
        color += diff * light->getColor() * light->getIntensity(); // Accumulate the light contribution
    }
    
    //Multiply the accumulated lighting by the material color
    vec3 result = color * materialColor;

    //Clamp the result to [0, 1] to ensure valid RGB values
    result = vec3(
        std::min(result.x(), 1.0f),
        std::min(result.y(), 1.0f),
        std::min(result.z(), 1.0f)
    );

    return result;
}