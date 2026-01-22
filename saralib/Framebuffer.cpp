#pragma once

#include <vector>
#include "vec.h"

class Framebuffer{
    public:
        //default constructor is 100x100
        Framebuffer();
        
        //Specify size of img
        Framebuffer(int x, int y);


        /*TO-DO!!!!!!

         //sets entire image to one color
         void clearToColor(vec3 c);

        //linear interpolation gradient func, 2 colors

        //set a single pixel color

        //export as png. Need filename string input
        */

    private:
        int width, height;
        std::vector<vec3> fbStorage; //Framebuffer is a vector of ... vectors :0
};