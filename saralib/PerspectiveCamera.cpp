#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera()
  : Camera()
{
  l = -imagePlane_width/2.0;
  r = imagePlane_width/2.0;

  b = -imagePlane_height/2.0;
  t = imagePlane_height/2.0;
}

PerspectiveCamera::PerspectiveCamera(int pixel_nx, int pixel_ny)
  : Camera(pixel_nx, pixel_ny)
{
  l = -imagePlane_width/2.0;
  r = imagePlane_width/2.0;

  b = -imagePlane_height/2.0;
  t = imagePlane_height/2.0;
}

PerspectiveCamera::PerspectiveCamera(vec3 origin , vec3 viewdir , float focalLen , float imagePlaneWidth , float imagePlaneHeight, int pixel_nx, int pixel_ny) : Camera(origin, viewdir, focalLen, imagePlaneWidth, imagePlane_height, pixel_nx, pixel_ny)
{
  l = -imagePlane_width/2.0;
  r = imagePlane_width/2.0;

  b = -imagePlane_width/2.0;
  t = imagePlane_width/2.0;
}

ray PerspectiveCamera::generateRay(float i, float j)
{
  float u = l + (r - l) * i / (float)nx;
  float v = b + (t - b) * j / (float)ny;
  vec3 rayDir = -focalLength * W + u * U + v * V;

  return ray(pos, rayDir);
}