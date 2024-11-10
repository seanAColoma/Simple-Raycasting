#ifndef SPHERE_H
#define SPHERE_H


#include "hittable.h"


class sphere : public hittable {
    public:
        //ensure the radius is not negative
        sphere(const point3& center, double radius) : center(center), radius(std::fmax(0, radius)) {}


        bool hit(const ray& r, interval ray_t, hit_record& rec) const override{
            vec3 oc = center - r.origin();
            //a vector's dot product with itself is the square of its length
            auto a = r.direction().length_squared();
            //set h = -b/2 and simplifies well
            auto h = dot(r.direction(),oc);
            auto c = oc.length_squared() - radius * radius;
            auto discriminant = h*h - a*c;
            if(discriminant < 0) {
                return false;
            }
            auto sqrtd = std::sqrt(discriminant);
            //reformulate calculation for robustness - untested
            auto root = (h - sqrtd)/a;
               
            //if root found to be not wihin bounds, calculate second root
            if(!ray_t.surrounds(root)) {
                //normal formulation is numerically stable
                root = (h+sqrtd)/a;
                if(!ray_t.surrounds(root)) {
                        return false;
                }
               
            }  
            rec.t = root;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center)/radius;
            rec.set_face_normal(r, outward_normal);
            return true;
        }
    private:
        point3 center;
        double radius;
};




#endif







