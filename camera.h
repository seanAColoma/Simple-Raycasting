#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"

class camera {
    public:
        //should be setting in owning code before render() is called
        int img_width = 100;
        double aspect_ratio = 16.0/9.0;
        int samples_per_pixel = 10;

        void render(const hittable& world) {
            int maxColor = 255;
            initialize();
            //header
            std::cout << "P3\n" << img_width << " " << img_height << "\n" << maxColor << "\n";
            //image values
            for(int j = 0; j<img_height; j++){

                //progress reporting
                std::clog << "\rScanlines Remaining: " << (img_height - j) << ' ' << std::flush;
                for(int i = 0; i<img_width; i++){
                    color pixel_color(0,0,0);
                    for(int sample = 0; sample<samples_per_pixel; sample++) {
                        ray r = get_rand_ray(i,j);
                        pixel_color += ray_color(r, world);
                    }
                    write_color(std::cout, pixel_sample_scale*pixel_color);
                }
            }
    std::clog << "\n\rdone! :D      \n";
        }

    private:
        int img_height;
        double pixel_sample_scale; 
        point3 camera_center;
        point3 pixel00_loc;
        vec3 pixel_delta_u;
        vec3 pixel_delta_v;


        void initialize() {
            img_height = int(img_width/aspect_ratio);
            //make sure img_height is at least 1
            img_height = (img_height < 1) ? 1 : img_height;

            //camera center
            auto camera_center = point3(0,0,0);

            //set scaling factor for average color for pixel
            pixel_sample_scale = 1.0/samples_per_pixel;

            //world
            hittable_list world;
            world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
            world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));
            //camera
            auto focal_length = 1.0;
            //viewport height, width are real values - they define the size of a plane (the viewport) in 3d space
            auto viewport_height = 2.0;
            auto viewport_width  = viewport_height * (double(img_width)/img_height);

            //the vector in 3d space along the horizontal edge
            auto viewport_u = vec3(viewport_width, 0, 0);
            //the vector in 3d space along the vertical edge (pointing downwards)
            auto viewport_v = vec3(0, -viewport_height, 0);

            //delta vectors: vector inbetween pixels
            pixel_delta_u = viewport_u/img_width;
            pixel_delta_v = viewport_v/img_height;

            //calculate the location of the upper left corner of the viewport
            auto viewport_upper_left = camera_center - vec3(0,0,focal_length) - viewport_u/2 - viewport_v/2;
            //calculate the location (in 3d space) of the upper left pixel (in the image) relative to the camera
            //outer edge of pixels 0.5 distance away from edge of viewport
            pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
        }

        //return the color of a ray
        color ray_color(const ray& r, const hittable& world) const {
            hit_record rec;
            if(world.hit(r, interval(0, infinity), rec)) {
                //shade sphere with surface normal
                return 0.5 * (rec.normal + color(1,1,1));
            }

            //linear interpolation based on y coordinate to create white to blue gradient
            vec3 unit_direction = unit_vector(r.direction());
            auto a = 0.5*(unit_direction.y() + 1.0);
            return (1.0-a)*color(1.0,1.0,1.0) + a*color(0.5, 0.7, 1.0);
        }

        ray get_rand_ray(int i, int j) {
            auto offset = sample_square();
            //random pixel sample at i, j
            auto pixel_sample = pixel00_loc + ((i + offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v);
            //originates at camera center
            auto ray_origin = camera_center;
            auto ray_direction = pixel_sample - ray_origin;
            return ray(ray_origin, ray_direction);

        }

        vec3 sample_square() const {
            return vec3(random_double() - 0.5, random_double() + 0.5, 0);
        }
};
#endif