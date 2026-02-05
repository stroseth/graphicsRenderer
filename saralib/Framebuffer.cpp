#include "Framebuffer.h"
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

// do you want this constructor??
// Commented out since it doesn't exist in header
// 
// Framebuffer::Framebuffer(color c)
// {
// }

void Framebuffer::clearToColor(color c)
{
}


//set a single pixel color
void Framebuffer::setPixelColor(int i, int j, color c)
{
}

void Framebuffer::setPixelColor(int index, color c)
{
}


        //linear interpolation gradient func, 2 colors

void Framebuffer::exportAsPNG()
{
}
