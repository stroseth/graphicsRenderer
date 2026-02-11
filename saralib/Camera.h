//base class for camera. Contains info on how scene should be rendered

#pragma once

class Camera{
    public:
        //default camera
        Camera() : pos(0,0,0),
            u(1,0,0), v(0,1,0), w(0,0,1),
            focalLength(1.0), //one = one unit of my choice
            imageplane_width(0.25), imageplane_height(0.25)
        {}
        virtual -Camera(){}

        virtual ray generateRay(int i, int j) = 0;

    protected:

    vec3 pos;

    //basis vectors for camera
    vec3 u,v,w;

    float focalLength; //d or distance. can pick whatever unit but be consistent with it.
    float imageplane_width, imageplane_height; //how big is the img plane
}