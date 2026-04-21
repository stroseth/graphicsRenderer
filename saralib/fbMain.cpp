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
#include "RayTracer.h"
#include "MirrorShader.h"

int main(int argc, char *argv[])
{
  Framebuffer fb(400, 400);

  std::vector<std::shared_ptr<Shape>> shapes;

  // Default Camera: focal length = 0.7, image plane width = 0.5
  PerspectiveCamera cam(vec3(0, 0, 0), vec3(0, 0, -1), 1.0, 0.5, 0.5, 400, 400);

  //create shaders
  auto lambertianShader = std::make_shared<LambertianShader>();
  auto blinnPhongShader = std::make_shared<BlinnPhongShader>();
  auto mirrorShader = std::make_shared<MirrorShader>();
  blinnPhongShader->setEyePosition(cam.getPosition());

  //Make shapes
  shapes.push_back(std::make_shared<Sphere>(
    vec3(0, 0, -2.5), 0.5f, vec3(0.3, 0.8, 0.3), blinnPhongShader));
 shapes.push_back(std::make_shared<Sphere>(
    vec3(0, 0, -1), 0.1f, vec3(0.3, 0.0, 0.3), mirrorShader));


  //Make light
  std::vector<std::shared_ptr<PointLight>> lights;
  lights.push_back(std::make_shared<PointLight>());


  for (int x = 0; x < fb.getFbWidth(); x++) {
    for (int y = 0; y < fb.getFbHeight(); y++) {
      ray r = cam.generateRay(x, y);
      vec3 pixelColor = computeRayColor(r, shapes, lights, 2);
      fb.setPixelColor(x, y, pixelColor);
    }
  }

  fb.exportAsPNG("mirrorTest.png");

  return 0;
}