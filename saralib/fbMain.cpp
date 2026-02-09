#include "Framebuffer.h"
#include "vec3.h"

using color = vec3;

int main(int argc , char* argv []) {
    Framebuffer fb1;
    color blue = color(.4, .223, .991); //color must be floats
    fb1.clearToColor(blue);
    fb1.exportAsPNG("fb1.png");
}