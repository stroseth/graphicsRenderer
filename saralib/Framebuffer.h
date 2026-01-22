#pragma once

#include <vector>
#include "vec.h"

using color = vec3;

class Framebuffer{
    public:
        //default constructor is 100x100
        Framebuffer();
        
        //Specify size of img
        Framebuffer(int x, int y);


        //TO-DO!!!!!!

         //sets entire image to one color
         void clearToColor(color c);

        //set a single pixel color
        void setPixelColor(int i, int j, color c);
        void setPixelColor(int index, color c);

        //linear interpolation gradient func, 2 colors

        void exportAsPNG(){};
        //export as png. Need filename string input

    private:
        int width, height;
        std::vector<vec3> fbStorage; //Framebuffer is a vector of ... vectors :0
};