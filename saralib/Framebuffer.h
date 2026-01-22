#include "Framebuffer.h"

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