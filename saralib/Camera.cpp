#include "Camera.h"

Camera::Camera()
    : pos(0,0,0), U(1,0,0), V(0,1,0), W(0,0,1),
      focalLength(1.0), imagePlane_width(0.25), imagePlane_height(0.25),
      nx(100), ny(100)
{}

Camera::Camera(int pixel_nx, int pixel_ny)
    : pos(0,0,0), U(1,0,0), V(0,1,0), W(0,0,1),
      focalLength(.1), imagePlane_width(0.25), imagePlane_height(0.25),
      nx(pixel_nx), ny(pixel_ny)
{}

Camera::Camera(vec3 origin , vec3 viewdir , float focalLen , float imagePlaneWidth, int pixel_nx, int pixel_ny) 
    : pos(origin), focalLength(focalLen),
      imagePlane_width(imagePlaneWidth),
      nx(pixel_nx), ny(pixel_ny)
{
     vec3 b = {0,1,0};

     W = -unit_vector(viewdir);
     U = (cross(b,W))/cross(b,W).length();
     V = cross(W,U);


}