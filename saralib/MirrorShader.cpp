#include "MirrorShader.h"
#include "RayTracer.h"
#include "ray.h"
#include "vec3.h"

vec3 MirrorShader::rayColor(const HitStruct& h,
            const ray &r,
            const std::vector<std::shared_ptr<PointLight>>& lights,
            const std::vector<std::shared_ptr<Shape>> &shapes,
            int depth)
{
    vec3 D = unit_vector(r.direction());
    vec3 N = unit_vector(h.normal);
    vec3 reflected = D - 2.0 * dot(D, N) * N;

    const double epsilon = 0.001;
    ray reflectedRay(h.point + N * epsilon, reflected);

    return computeRayColor(reflectedRay, shapes, lights, depth - 1);
}