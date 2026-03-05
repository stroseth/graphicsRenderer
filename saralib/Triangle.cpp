#include "Triangle.h"


/*
    // ~ Set up edge vectors and ray parameters (a-l represent vector components)
    // ~ Compute intermediate values for the algorithm (ei_hf, gf_id, dh_eg, M)
    // ~ Calculate the intersection parameter t and barycentric coordinates beta and gamma
    // ~ Check if t is within the valid range [t_min, t_max]
    // ~ Check if the barycentric coordinates are valid (inside or on the triangle boundary)
    // ~ Store the intersection point, parameter t, and shape reference in HitStruct if hit
*/
bool Triangle::intersect(const ray& r, float t_min, float& t_max, HitStruct& hit) const override{
    
    // ~ Set up edge vectors and ray parameters (a-l represent vector components)
    double a = vertex_a.x() - vertex_b.x();
    double b = vertex_a.x() - vertex_c.x();
    double c = r.direction.x();
    
    double d = vertex_a.y() - vertex_b.y();
    double e = vertex_a.y() - vertex_c.y();
    double f = r.direction.y();

    double g = vertex_a.z() - vertex_b.z();
    double h= vertex_a.z() - vertex_c.z();
    double i = r.direction.z();

    double j = vertex_a.x() - r.origin.x();
    double k = vertex_a.y() - r.origin.y();
    double l = vertex_a.z() - r.origin.z();

    // ~ Compute intermediate values for the algorithm (ei_hf, gf_di, dh_eg, M)
    double ei_hf = e*i - h*f;
    double gf_di = g*f - d*i;
    double dh_eg = d*h - e*g;
    double M = a*ei_hf + b*gf_di + c*dh_eg;

    // ~ Calculate the intersection parameter t and barycentric coordinates beta and gamma
    double t = (-1*(a*k - j*b) + e*(j*c - a*l) + d*(b*l-k*c))/M;

    // ~ Check if t is within the valid range [t_min, t_max]
    if (t < t_min || t > t_max) {return false;}
    else
    {    //coordinate check
        double gamma = (i*(a*k-j*b) + e*(j*c-a*l) + g*(b*l-k*c))/M;
        if (gamma < 0 || gamma > 1){return false};
        else
        {
            double beta = (j*ei_hf + k*gf_di + l*dh_eg)/M;
            if (beta < 0 || beta > 1) {return false};
            else{  // ~ Store the intersection point, parameter t, and shape reference in HitStruct if hit
                t_max = t;
                hit.t = t;
                hit.point = r.at(t);
                hit.shape = this;
                return true;
            }
        }
    }
    return false;
}

vec3 Triangle::getColor() const override{
    return color;
}