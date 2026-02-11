#include "Framebuffer.h"
#include "vec3.h"

using color = vec3;

int main(int argc , char* argv []) {
    Framebuffer fb1{600,600};
    color blue = color(.4f, .223f, .991f); //color must be floats
    //fb1.clearToColor(blue);
    //fb1.exportAsPNG("fb1.png");
    color green = color(.0f, .8f, .0f); //geen
    fb1.clearToGradient(blue, green);
    fb1.exportAsPNG("HopefullyAGradient.png");
}