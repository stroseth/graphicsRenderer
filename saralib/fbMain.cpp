#include "Framebuffer.h"
#include "vec3.h"

using color = vec3;

int main(int argc , char* argv []) {
    Framebuffer fb1;
    color blue = color(133, 226, 242);
    fb1.clearToColor(blue);
    fb1.exportAsPNG("fb1.png");
}