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

void Framebuffer::clearToGradient(color c0, color c1){
  for (auto x=0; x<width; x++) {
    for (auto y=0; y<height; y++) {
      
      float t = y / (float)height;
  
      // need to loop over and lerp here... (pretty sure it do tho)
      color c2 = c0 * (1-t) + c1 * t;
  
      int idx = y * width + x;
      fbStorage[idx] = c2;
    }
  }
}

void Framebuffer::setPixelColor(int i, int j, color c){
    uint idx = j * width + i; 
    setPixelColor(idx, c);
}

void Framebuffer::setPixelColor(int index, color c){
    fbStorage[index] = color(c.x(), c.y(), c.z());
}


void Framebuffer::exportAsPNG(std::string filename){
    int w = width, h = height;
    png::image< png::rgb_pixel > imData( w, h );
    for (unsigned int idx=0; idx<imData.get_height()*imData.get_width(); ++idx)
    {
        size_t x = idx % w;
        size_t y = static_cast<size_t>( floor(idx / static_cast<float>(imData.get_width())) );

        //converts float val to int 0-255
        int redVal = round(fbStorage[idx].x() * 255);
        int blueVal = round(fbStorage[idx].y() * 255);
        int greenVal = round(fbStorage[idx].z() * 255);

        imData[height-1-y][x] = png::rgb_pixel(redVal,blueVal,greenVal);
    }
    imData.write(filename);
}
