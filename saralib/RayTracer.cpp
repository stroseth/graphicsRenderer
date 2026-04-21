#include "RayTracer.h"

#include "HitStruct.h"
#include "NormalShader.h"
#include "PointLight.h"
#include "Shape.h"
#include "Shader.h"

#include <limits>

vec3 computeRayColor(const ray &r,
    const std::vector<std::shared_ptr<Shape>> &shapes,
    const std::vector<std::shared_ptr<PointLight>> &lights,
    int depth )
{
    if (depth <= 0){
        return vec3(0.0, 0.0, 0.0);
    }

    float t_min = 0.001f;
    float t_max = std::numeric_limits<float>::max();

    HitStruct closestHit;
    closestHit.t = t_max;
    bool hitAnything = false;

    // Check intersection with all shapes, find closest
    for (const auto &shape : shapes) {
        HitStruct tempHit;
        if (shape->intersect(r, t_min, t_max, tempHit)) {
            if (tempHit.t < closestHit.t) {
                closestHit = tempHit;
                hitAnything = true;
                t_max = tempHit.t;
            }
        }
    }

    if (hitAnything) {
        auto shader = closestHit.shape->getShader();
        if (shader) {
            return shader->rayColor(closestHit, r, lights, shapes, depth);
        } else {
            NormalShader defaultShader;
            return defaultShader.rayColor(closestHit, r, lights, shapes, depth);
        }
    }

  // Background color
  vec3 unit_direction = unit_vector(r.direction());
  auto a = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - a) * vec3(1.0, 1.0, 1.0) + a * vec3(0.5, 0.7, 1.0);
  return vec3(1,1,1);
}