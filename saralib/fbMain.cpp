#include <iostream>
#include <vector>
#include <memory>
#include <limits>
#include "Framebuffer.h"
#include "PerspectiveCamera.h"
#include "ray.h"
#include "Shape.h"
#include "Sphere.h"
#include "Triangle.h"
#include "NormalShader.h"
#include "PointLight.h"
#include "LambertianShader.h"
#include "BlinnPhongShader.h"

vec3 computeRayColor(const ray &r, const std::vector<std::shared_ptr<Shape>> &shapes, const std::vector<std::shared_ptr<PointLight>> &lights)
{
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
      return shader->rayColor(closestHit, lights);
    } else {
      BlinnPhongShader defaultShader;
      return defaultShader.rayColor(closestHit, lights);
    }
  }

  // Background color
  //vec3 unit_direction = unit_vector(r.direction());
  //auto a = 0.5 * (unit_direction.y() + 1.0);
  //return (1.0 - a) * vec3(1.0, 1.0, 1.0) + a * vec3(0.5, 0.7, 1.0);
  return vec3(1,1,1);
}

int main(int argc, char *argv[])
{
  Framebuffer fb(200, 200);

  std::vector<std::shared_ptr<Shape>> shapes;

  // Default Camera: focal length = 0.7, image plane width = 0.5
   PerspectiveCamera cam(vec3(0, 0, 0), vec3(0, 0, -1), 1.0, 0.5, 0.5, 200, 200);

  //Make shapes
  shapes.push_back(std::make_shared<Triangle>(
    vec3(-0.15f,-0.15f,-1.5f), vec3(0.15f,-0.15f,-1.5f), vec3(0.0f,0.15f,-1.5f),
    vec3(1.0, 0.0, 0.7)));

  shapes.push_back(std::make_shared<Sphere>(vec3(.33f,-.023f, -2.1f), 0.5f, vec3(0.5f, 0, 0.5f)));

  //Make light
  std::vector<std::shared_ptr<PointLight>> lights;
  lights.push_back(std::make_shared<PointLight>());



  for (int x = 0; x < fb.getFbWidth(); x++) {
    for (int y = 0; y < fb.getFbHeight(); y++) {
      ray r = cam.generateRay(x, y);
      vec3 pixelColor = computeRayColor(r, shapes, lights);
      fb.setPixelColor(x, y, pixelColor);
    }
  }

  fb.exportAsPNG("blinnPTest.png");

  return 0;
}