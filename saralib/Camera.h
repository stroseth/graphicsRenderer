//base class for camera. Contains info on how scene should be rendered
#pragma once

#include "ray.h"

class Camera{
    public:
        //default camera
        Camera(); // default pixel img dimensions are 100x100
        Camera(int pixel_nx, int pixel_ny); //input pixel image dimensions
        Camera(vec3 origin , vec3 viewdir , float focalLength , float imagePlaneWidth , float imagePlaneHeight, int pixel_nx, int pixel_ny);
        virtual ray generateRay(int i, int j) = 0;
        virtual ray generateRay(float i, float j) = 0;
        vec3 getPosition() { return pos; }

    protected:
        vec3 pos; //camera position

        //basis vectors for camera
        vec3 U,V,W;

        float focalLength; //d or distance. can pick whatever unit but be consistent with it.
        float imagePlane_width, imagePlane_height; //how big is the img plane

        int nx, ny;
};