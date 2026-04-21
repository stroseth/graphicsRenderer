#include "BlinnPhongShader.h"

vec3 BlinnPhongShader::rayColor(const HitStruct& h, const std::vector<std::shared_ptr<PointLight>>& lights){
    return vec3(0.0f, 0.0f, 0.0f);
}