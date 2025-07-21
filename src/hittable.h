#ifndef HITTABLE_H
#define HITTABLE_H
#include "rtweekend.h"

class hit_record {
    public:
    point3 p;
    vec3 normal;
    double t;
    bool front_face;

    void set_face_normal(const ray& r, const vec3& outward_normal) {
    //Note: The parameter "outward_normal" is assumed to have unit length.
    //Sets the hit record normal vector. 
    
    front_face = dot(r.direction(), outward_normal) < 0; //Is the ray direction front facing
    normal = front_face ? outward_normal : -outward_normal; //If it is not, the normal goes in the opposite direction (front facing)
    }
};
class hittable {
    public:
    virtual ~hittable() = default;

    virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};

#endif