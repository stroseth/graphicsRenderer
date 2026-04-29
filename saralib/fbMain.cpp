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
#include "DiffuseShader.h"
#include "handleGraphicsArgs.h"

float randomOffset(){
  static std::uniform_real_distribution<float> distribution(0.0, 1.0);
  static std::mt19937 generator;
  return distribution(generator);
}

int main(int argc, char *argv[])
{
  sivelab::GraphicsArgs arguments;
  arguments.process(argc, argv);

  //Framebuffer fb(arguments.width, arguments.height);
  Framebuffer fb(900, 750);
  float aspectRatio = arguments.aspectRatio;
  std::string outputFileName = arguments.outputFileName + ".png";
  int maxDepth = arguments.recursionDepth;
  int rpp_NSquare = arguments.rpp;

   // Camera setup
  PerspectiveCamera cam(vec3(-1.5, 2.5, 2.5), vec3(0, -.8, -3.0), 0.6, 1, 0.83, fb.getFbWidth(), fb.getFbHeight());
  //PerspectiveCamera cam(vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, -3.0), 0.4, 0.6, 0.6, fb.getFbWidth(), fb.getFbHeight());
  // Create scene with spheres
  std::vector<std::shared_ptr<Shape>> shapes;

  // Create shaders
  auto lambertianShader = std::make_shared<LambertianShader>();
  auto blinnPhongShader = std::make_shared<BlinnPhongShader>();
  blinnPhongShader->setEyePosition(cam.getPosition());
  auto mirrorShader = std::make_shared<MirrorShader>();
  auto diffuseGroundShader = std::make_shared<DiffuseShader>(vec3(0.8, 0.8, 0.8));


  // Create lights
  std::vector<std::shared_ptr<PointLight>> lights;
  lights.push_back(std::make_shared<PointLight>(vec3(3, 7, 2), vec3(1.0, 1.0, 1.0)));
  lights.push_back(std::make_shared<PointLight>(vec3(0, 5, -4), vec3(1.0, 1.0, 1.0)));

  // Ground plane: Diffuse shader
  shapes.push_back(std::make_shared<Triangle>(
    vec3(0, -1.0, 50), vec3(200, -1.0, -200), vec3(-200, -1.0, -200), vec3(0.8, 0.8, 0.8), diffuseGroundShader));
  
  //wall
  shapes.push_back(std::make_shared<Triangle>(
    vec3(-20,0,-4), vec3(20, 0, -4), vec3(-20, 10, -4), vec3(.9098,.9098,.9098), lambertianShader
  ));
  shapes.push_back(std::make_shared<Triangle>(
    vec3(20,0,-4), vec3(20, 10, -4), vec3(-20, 10, -4), vec3(.9098,.9098,.9098), lambertianShader
  ));

  //buge mirrore
  shapes.push_back(std::make_shared<Triangle>(
    vec3(-3, 0.0, -3.5), vec3(3, 0.0, -3.5), vec3(-3, 3, -3.5), vec3(1.0, 0.0, 0.0), mirrorShader
  ));
  shapes.push_back(std::make_shared<Triangle>(
    vec3(3, 0.0, -3.5), vec3(3, 3, -3.5), vec3(-3, 3, -3.5), vec3(0.0,0.0,1.0), mirrorShader
  ));

  //mirror border
  shapes.push_back(std::make_shared<Triangle>(
    vec3(-3.2, 0.0, -3.5), vec3(3.2, 0.0, -3.5), vec3(-3.2, 3.2, -3.5), vec3(.5372, 0.318, 0.1608), blinnPhongShader
  ));
  shapes.push_back(std::make_shared<Triangle>(
    vec3(3.2, 0.0, -3.5), vec3(3.2, 3.2, -3.5), vec3(-3.2, 3.2, -3.5), vec3(0.5372,0.318,0.1608), blinnPhongShader
  ));

  // Buge components
    //head
  shapes.push_back(std::make_shared<Sphere>(
    vec3(0,0,-1), 0.92f, vec3(1.0, 0.0, 0.0), blinnPhongShader));

  for (int i = 0; i < 5; i++){
  shapes.push_back(std::make_shared<Sphere>(
    vec3(0,0,(0+i)), 1.0f, vec3(0.1, 1.0, 0.25), lambertianShader));
  }

    //oh yeah it's antennae time
  shapes.push_back(std::make_shared<Triangle>(
    vec3(-0.5,1.5,-1), vec3(-.4,1.5, -1), vec3(-.6, 0.0, -1), vec3(0.0, 1.0, 0.0), lambertianShader
  )); //incorrect winding order here because i actually WANT the front of the buge to be at the mirror

  shapes.push_back(std::make_shared<Triangle>(
    vec3(0.5, 1.5, -1), vec3(.4, 1.5, -1), vec3(.6, 0.0, -1), vec3(0.0, 1.0, 0.0), lambertianShader
  ));

  shapes.push_back(std::make_shared<Sphere>(
    vec3(0.5, 1.5, -1.05), 0.1f, vec3(0.1, 1.0, 0.25), blinnPhongShader));
  shapes.push_back(std::make_shared<Sphere>(
    vec3(-0.5, 1.5, -1.05), 0.1f, vec3(0.1, 1.0, 0.25), blinnPhongShader));

    //another mirror?
shapes.push_back(std::make_shared<Triangle>(
    vec3(-3, 0.0, 7.5), vec3(-3, 3, 7.5), vec3(3, 0.0, 7.5), vec3(1.0, 0.0, 0.0), mirrorShader
  ));
  shapes.push_back(std::make_shared<Triangle>(
    vec3(3, 0.0, 7.5), vec3(-3, 3, 7.5), vec3(3, 3, 7.5), vec3(0.0,0.0,1.0), mirrorShader
  ));

    //wall
  shapes.push_back(std::make_shared<Triangle>(
    vec3(-20,0,8), vec3(-20, 10, 8), vec3(20, 0, 8), vec3(.9098,.9098,.9098), lambertianShader
  ));
  shapes.push_back(std::make_shared<Triangle>(
    vec3(20,0,8), vec3(-20, 10, 8), vec3(20, 10, 8), vec3(.9098,.9098,.9098), lambertianShader
  ));


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

  fb.exportAsPNG(outputFileName);

  return 0;
}