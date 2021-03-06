#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable{
    public:
        point3 center;
        double radius;

        sphere() {}
        sphere(point3 center, double r) : center(center), radius(r) {};

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& record) const override;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& record) const {
    vec3 oc = r.origin() - center;
    auto a  =r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;
    
    auto discriminant = half_b*half_b - a*c;
    if (discriminant<0)return false;
    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if(root < t_min || t_max < root)
            return false;
    }
    
    record.t = root;
    record.p = r.at(record.t);
    vec3 outward_normal = (record.p - center) / radius;
    record.set_face_normal(r, outward_normal);

    return true;
}

#endif