//base class for camera. Contains info on how scene should be rendered

#pragma once

class Camera{
    public:
        //default camera
        Camera(); // default pixel img dimensions are 100x100
        Camera(int pixel_nx, int pixel_ny); //input pixel image dimensions
        virtual -Camera(){}

        virtual ray generateRay(int i, int j) = 0;

    protected:
        vec3 pos; //camera position

        //basis vectors for camera
        vec3 U,V,W;

        float focalLength; //d or distance. can pick whatever unit but be consistent with it.
        float imageplane_width, imageplane_height; //how big is the img plane

        int nx, ny;
}