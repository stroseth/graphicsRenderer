#include "NormalShader.h"

//this function rescales the normal from range [-1,1] to [0,1] to allow RGB visualization
vec3 NormalShader::rayColor(const HitStruct& hit, const std::vector<std::shared_ptr<PointLight>>& lights){
    vec3 normalizedNormal = (hit.normal + vec3(1.0,1.0,1.0)) * 0.5;
    return normalizedNormal;
}