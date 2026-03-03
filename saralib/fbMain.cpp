#include "Framebuffer.h"
#include "vec3.h"
#include "PerspectiveCamera.h"

using color = vec3;

int main(int argc , char* argv []) {
    color blue = color(.4f, .223f, .991f);
    color green = color(.0f, .8f, .0f);
    /*Framebuffer fb1{600,600};
     //color must be floats
    //fb1.clearToColor(blue);
    //fb1.exportAsPNG("fb1.png");
    fb1.clearToGradient(blue, green);
    fb1.exportAsPNG("HopefullyAGradient.png");
    */

    Framebuffer fb{200,200};
    //fb.clearToColor(blue);
    
    vec3 org = {20,10,5};
    vec3 view = {4,-2,7};
    float focal = .25f;
    float widHeight = .5f;

    // set default cam variables here
    PerspectiveCamera p = PerspectiveCamera( org , view , focal ,widHeight , widHeight, 200, 200 );
    for (int x=0; x <200; ++x) {
        for (int y=0; y <200; ++y) {
            ray r = p.generateRay(x, y);
            color ray_dir_color = unit_vector(r.direction());
            ray_dir_color = (ray_dir_color + vec3(1,1,1)) * 0.5;
            fb.setPixelColor(x, y, ray_dir_color );
        }
    }
    fb.exportAsPNG( "defaultCamRayColors.png" );
}