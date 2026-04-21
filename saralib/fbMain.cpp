#include <iostream>
#include <vector>
#include <memory>
#include <limits>
#include <random>

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

float randomOffset(){
  static std::uniform_real_distribution<float> distribution(0.0, 1.0);
  static std::mt19937 generator;
  return distribution(generator);
}

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

  //antialiasing start
  int rpp_NSquare = 4;
  int maxDepth = 2;

  for (int x = 0; x < fb.getFbWidth(); x++) {
    for (int y = 0; y < fb.getFbHeight(); y++) {
      vec3 accumulatedColor(0.0, 0.0, 0.0);

      //stratified sampling
      for (int p = 0; p < rpp_NSquare; p++){
        for (int q = 0; q < rpp_NSquare; q++){
          float pOffset = (p + randomOffset()) / rpp_NSquare;
          float qOffset = (q + randomOffset()) / rpp_NSquare;

          ray r = cam.generateRay(x + pOffset, y + qOffset);    
          accumulatedColor += computeRayColor(r, shapes, lights, maxDepth);
        }
      }

      vec3 pixelColor = accumulatedColor / (float)(rpp_NSquare * rpp_NSquare);
      fb.setPixelColor(x, y, pixelColor);
    }
  }

  fb.exportAsPNG("4antialias.png");

  return 0;
}