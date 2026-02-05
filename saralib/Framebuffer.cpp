#include <iostream>
#include <cstdlib>
#include <cstring>

#include "Framebuffer.h"
#include "png++/png.hpp"

using color = vec3;

//default constructor: allocates 100x100 vector for storage
Framebuffer::Framebuffer()
    : width(100), height(100), fbStorage(width*height)
    {
}

//constructor for specific sizes
Framebuffer::Framebuffer(int x, int y)
    : width(x), height(y), fbStorage(width*height)
    {
}

void Framebuffer::clearToColor(color c){
    for (auto idx =0u; idx <fbStorage.size (); ++ idx) {
        setPixelColor(idx, c);
    };
}

void Framebuffer::setPixelColor(int i, int j, color c){
    ///Need to implement!
}

void Framebuffer::setPixelColor(int index, color c){
    fbStorage[idx] = color(c.x(), c.y(), c.z());
}


void Framebuffer::exportAsPNG(std::string filename){
    int w = width, h = height;
    png::image< png::rgb_pixel > imData( w, h );
    for (unsigned int idx=0; idx<imData.get_height()*imData.get_width(); ++idx)
    {
        size_t x = idx % w;
        size_t y = static_cast<size_t>( floor(idx / static_cast<float>(imData.get_width())) );

        imData[y][x] = png::rgb_pixel(fbStorage[idx].x(),fbStorage[idx].y(),fbStorage[idx].z());
    }
    imData.write(filename);
}