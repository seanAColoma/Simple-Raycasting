#include <iostream>
#include "color.h"
#include "vec3.h"
#include "ray.h"

double hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = center - r.origin();
    auto a = dot(r.direction(), r.direction());
    auto b = -2.0*dot(r.direction(), (oc));
    auto c = dot(oc,oc) - (radius * radius);
    auto discriminant = b*b - 4*a*c;
    
    if(discriminant < 0) {
        return -1.0;
    }
    else {
        //we use the - discriminant form since we want the smallest t ie the first time the ray hits the sphere
        return(-b - std::sqrt(discriminant)) / (2.0*a);
    }
}
//returns the color of a ray
color ray_color(const ray& r) {
    auto t = hit_sphere(point3(0,0,-1), 0.5, r);
    if(t > 0.0) {
        vec3 N = unit_vector(r.at(t) - vec3(0,0,-1));
        return 0.5*color(N.x() + 1, N.y()+1, N.z()+1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    //linear interpolation based on y coordinate to create white to blue gradient
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0,1.0,1.0) + a*color(0.5, 0.7, 1.0);
}


int main() {
    int maxColor = 255;
    auto aspect_ratio = 16.0/9.0;
    //img width, height must be natural numbers - they define the number of pixels along each axiss
    int img_width = 400;
    int img_height = int(img_width/aspect_ratio);
    //make sure img_height is at least 1
    img_height = (img_height < 1) ? 1 : img_height;

    //camera
    auto focal_length = 1.0;
    //viewport height, width are real values - they define the size of a plane (the viewport) in 3d space
    auto viewport_height = 2.0;
    auto viewport_width  = viewport_height * (double(img_width)/img_height);
    auto camera_center = point3(0,0,0);

    //the vector in 3d space along the horizontal edge
    auto viewport_u = vec3(viewport_width, 0, 0);
    //the vector in 3d space along the vertical edge (pointing downwards)
    auto viewport_v = vec3(0, -viewport_height, 0);

    //delta vectors: vector inbetween pixels
    auto pixel_delta_u = viewport_u/img_width;
    auto pixel_delta_v = viewport_v/img_height;

    //calculate the location of the upper left corner of the viewport
    auto viewport_upper_left = camera_center - vec3(0,0,focal_length) - viewport_u/2 - viewport_v/2;
    //calculate the location (in 3d space) of the upper left pixel (in the image) relative to the camera
    //outer edge of pixels 0.5 distance away from edge of viewport
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    //P3 (header)
    //img_width, img_height (image dimensions)
    //255 (maximum color intensity)
    std::cout << "P3\n" << img_width << " " << img_height << "\n" << maxColor << "\n";

    //image values
    for(int j = 0; j<img_height; j++){
        //progress reporting
        std::clog << "\rScanlines Remaining: " << (img_height - 1) << ' ' << std::flush;
        for(int i = 0; i<img_width; i++){
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\rdone! :D      \n";
}