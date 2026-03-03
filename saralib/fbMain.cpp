#include <memory>

#include "Framebuffer.h"
#include "vec3.h"
#include "PerspectiveCamera.h"
#include "ray.h"
#include "Shape.h"
#include "Sphere.h"
#include "HitStruct.h"

using color = vec3;

int main(int argc , char* argv []) {
    //void rayToColor(); //ray-to-color funct

    //FB and colors
    Framebuffer fb0{600, 300};
    color sphereColor(1,0,0);
    color bg(1,1,1);

    //Camera setup
     PerspectiveCamera p(vec3(0, 0, 0), vec3(0, 0, -1), 0.7, 0.5, 0.5, fb0.getFbWidth(), fb0.getFbHeight());
  
    //Sphere Info
    std::shared_ptr<Shape> s = std::make_shared<Sphere>(point3(0, -1.25, -7), 0.3f, vec3(1,1,1));

    float tmin = 0.001f;
    float tmax = std::numeric_limits<float>::infinity();
    HitStruct h;

    for (int x = 0; x < fb0.getFbWidth(); ++x){
        for (int y=0; y<fb0.getFbHeight(); ++y){
            ray r = p.generateRay(x,y);

            if (s->intersect(r,tmin, tmax, h)){
                fb0.setPixelColor(x,y, sphereColor);
            }
            else{
                fb0.setPixelColor(x,y,bg);
            };
        };
    };

    fb0.exportAsPNG("Flag_maybe.png");
}

/*
void rayToColor(){
    Framebuffer fb{200,200};
    //fb.clearToColor(blue);
    
    vec3 org = {20,10,5};
    vec3 view = {4,-2,7};
    float focal = .25f;
    float widHeight = .5f;

    // set default cam variables here
    PerspectiveCamera p = PerspectiveCamera( org , view , focal ,fb.getFbWidth(), fb.getFbHeight(), 200, 200 );
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
*/