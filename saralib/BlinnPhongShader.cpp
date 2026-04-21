#include "BlinnPhongShader.h"
#include "Shape.h"

vec3 BlinnPhongShader::rayColor(const HitStruct& h, const std::vector<std::shared_ptr<PointLight>>& lights){
    vec3 materialColor = h.shape->getColor();
    vec3 color = vec3(0.0, 0.0, 0.0);

    //material coefficients: kd for diffuse, ks for specular, p for phong exponent
    /***HARDCODED FOR NOW; should put as parameters of the shader class ***/
    float kd = 1.0f;
    float ks = 0.6f;
    float p = 32.0f;

    //compute view direction from hit point toward eye position
    vec3 V = unit_vector(eyePos - h.point);

    for (const auto& light : lights){
        vec3 L = unit_vector(light->getPosition() - h.point); //calculate light dir from hit point toward light
        vec3 H = unit_vector(L + V); //half-vector (bisector btwn light and view)

        //diffuse term: L = kd* I * max(0, n dot l)
        float diff = std::max(dot(h.normal, L), 0.0f);
        vec3 diffuse = kd * diff * light->getColor() * light->getIntensity();

        //specular term: L = ks * I * max(0, n dot h) ^ p
        float spec = std::pow(std::max(dot(h.normal, H), 0.0f), p);
        vec3 specular = ks * spec * light->getColor() * light->getIntensity();

        color += diffuse * materialColor + specular;
    }

    //clamp to [0,1]
    vec3 result = vec3(
        std::min(color.x(), 1.0f),
        std::min(color.y(), 1.0f),
        std::min(color.z(), 1.0f)
    );
    
    return result;
}