#pragma once

#include "Camera.h"

class PerspectiveCamera : public Camera
{
public:
  PerspectiveCamera();
  PerspectiveCamera(int pixel_nx, int pixel_ny);

  PerspectiveCamera(vec3 origin , vec3 viewdir , float focalLen , float imagePlaneWidth ,  int pixel_nx, int pixel_ny);

  ray generateRay( int i, int j ) override
  {
    float u, v;
    u = l + (r-l) * (i+0.5)/(float)nx;
    v = b + (t-b) * (j+0.5)/(float)ny;
    
    ray tempRay( pos, -W*focalLength + U*u + V*v );
    return tempRay;
  }

private:
  float l, r, b, t;
};


