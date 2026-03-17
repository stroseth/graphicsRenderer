#include "Sphere.h"

/*  Intersect function.
        Uses implicit line equation to determine whether the ray misses, tangents, or intersects the Sphere object.
        Returns false if miss
        Returns true if tangent or intersect  */
bool Sphere::intersect(const ray& r, float t_min, float& t_max, HitStruct& hit) const{

    //calculate eye minus center
    vec3 oc = r.origin() - center;
    
    //calculate discriminant
    float a = dot(r.direction(), r.direction());
    float b = 2.0f * (dot(oc, r.direction()));
    float c = dot(oc,oc) - radius*radius;

    float discriminant = b*b - 4*a*c;

    //if discriminant is less than zero, ray misses the sphere
    if (discriminant < 0) return false;

    //calculate t values
    float sqrtDiscriminant = std::sqrt(discriminant);

    float t1 = ((-1*b) - sqrtDiscriminant)/(2*a);
    float t2 = ((-1*b) + sqrtDiscriminant)/(2*a);

        /// check logic here
    // find which t value is closest and then see if that's within the t_min and t_max
    //handle t values
    if ((t1 > t_min) && (t1 < t_max)){
        t_max = t1;
        hit.t = t1;
        hit.point = r.at(t1);
        hit.shape = this;
        return true;
    }

    if ((t2 > t_min) && (t2 < t_max)){
        t_max = t2;
        hit.t = t2;
        hit.point = r.at(t2);
        hit.shape = this;
        return true;
    }
    return false;
}

//color getter
vec3 Sphere::getColor() const{
    return color;
}

//other getters
float Sphere::getRadius() const{
    return radius;
}

point3 Sphere::getCenter() const{
    return center;
}

//Shader getter
std::shared_ptr<Shader> Sphere::getShader() const{
    return shader;
}

//Shader setter
void Sphere::setShader(std::shared_ptr<Shader> shd){
    shader = shd;
}