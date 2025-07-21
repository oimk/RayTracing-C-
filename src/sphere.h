#ifndef SPHERE_H
#define SPHERE_H
#include "hittable.h"

class sphere : public hittable {
    public: 
        sphere(const point3& center, double radius) : center(center), radius(std::fmax(0,radius)) {}

 bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
    //caculates if a ray hit the sphere
    vec3 oc = center - r.origin();
    auto a = r.direction().length_squared();
    auto h = dot(r.direction(), oc);
    auto c = oc.length_squared() - radius*radius;
    auto discriminant = h*h - a*c;

    //check the interval
    if (discriminant < 0) {
        return false;
    } 
    auto sqrtd = std::sqrt(discriminant);

    auto root = (h-sqrtd) / a;
    if (!ray_t.surrounds(root)) {
        root = (h+sqrtd) /a;
        if (!ray_t.surrounds(root)){
            return false;
        }
    }
    rec.t = root; //At what interval does it hit
    rec.p = r.at(rec.t); //What are the cordinates of it hitting
    vec3 outward_normal = (rec.p - center) / radius; //Caculates the normal
    rec.set_face_normal(r, outward_normal); //Make sure the direction points forward
    return true; 
 }
 private:
 point3 center;
 double radius;
};
#endif 