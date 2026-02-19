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

    Framebuffer fb{800,800};
    //fb.clearToColor(blue);
    
    // set default cam variables here
    PerspectiveCamera p = PerspectiveCamera(800, 800);
    // PerspectiveCamera p( origin , viewdir , focalLength ,
    // imagePlaneWidth , fb.width(), fb.height () );
    for (int x=0; x <800; ++x) {
        for (int y=0; y <800; ++y) {
            ray r = p.generateRay(x, y);
            color ray_dir_color = unit_vector(r.direction());
            ray_dir_color = (ray_dir_color + vec3(1,1,1)) * 0.5;
            fb.setPixelColor(x, y, ray_dir_color );
        }
    }
    fb.exportAsPNG( "defaultCamRayColors.png" );
}