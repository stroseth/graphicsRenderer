#include "Sphere.h"

/*  Intersect function.
        Uses implicit line equation to determine whether the ray misses, tangents, or intersects the Sphere object.
        Returns false if miss
        Returns true if tangent or intersect  */
bool Sphere::intersect(const ray& r, float t_min, float& t_max, HitStruct& hit) const{

    //calculate eye minus center
    vec3 eyeMinusCenter = r.origin() - center;
    
    //calculate discriminant
    float A = dot(r.direction(), r.direction());
    float B = dot((2*r.direction()),eyeMinusCenter);
    float C = (dot(eyeMinusCenter, eyeMinusCenter) - (radius*radius));

    float discriminant = B*B - 4*(A-C);

    //if discriminant is less than zero, ray misses the sphere
    if discriminant < 0 return false;

    //calculate t values
    float sqrtDiscriminant = std::sqrt(discriminant);

    float t1 = ((-1*B) - sqrtDiscriminant)/2A;
    float t2 = ((-1*B) + sqrtDiscriminant)/2A;

    //handle t values
    if (t1 > t_min) && (t1 < t_max){
        t_max = t1;
        hit.t = t1;
        hit.point = r.at(t1);
        hit.shape = this;
        return true;
    }

    if (t2 > t_min) && (t2 < t_max){
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