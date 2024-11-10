#ifndef HITTABLE_H
#define HITTABLE_H


//store a record of some relevant values whenever a ray hits a hittable
class hit_record{
    public:
        //the 3d point where the ray hit the object
        point3 p;
        //the normal vector on the surface of the object at p
        vec3 normal;
        //the t value corresponding to the point on the ray where the hit occured
        double t;
        //indicate whether the ray hits the front face or back face
        bool front_face;
        //normals all face outwards, so examine dot product to determine front_face
        void set_face_normal(const ray& r, const vec3& outward_normal) {
            front_face = dot(r.direction(), outward_normal) < 0;
            normal = front_face ? outward_normal : -outward_normal;  

        }
};

class hittable {
    public:
        virtual ~hittable() = default;
        virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};
#endif