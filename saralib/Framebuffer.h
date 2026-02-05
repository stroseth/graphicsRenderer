#pragma once

#include <vector>
#include "vec3.h"

using color = vec3;

class Framebuffer{
    public:
        //default constructor is 100x100
        Framebuffer();
        
        //Specify size of img
        Framebuffer(int x, int y);

        //Clears entire image to one color
        void clearToColor(color c);

        //Set a single pixel color
        void setPixelColor(int i, int j, color c);
        void setPixelColor(int index, color c);

        //linear interpolation gradient func, 2 colors
        void setGradient(color c1, color c2);

        //Export as png. Need filename string input
        void exportAsPNG(std::string filename);
        
    private:
        int width, height;
        std::vector<color> fbStorage; //Framebuffer is a vector of ... vectors :0 (colors to be specific)
};
