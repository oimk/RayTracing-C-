#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"

class camera {
  public:
    double aspect_ratio = 1.0;  
    int image_width  = 100;  
    int samples_per_pixel = 10; //Randoms samples for each pixel -antialiasing
    int max_depth = 10;

    void render(const hittable& world) {
        initialize();

        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for (int j = 0; j < image_height; j++) {
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; i++) {
                color pixel_color(0,0,0);
                for (int sample = 0; sample < samples_per_pixel; sample++) {
                    ray r = get_ray(i, j); //Gets random ray from the pixel location
                    pixel_color += ray_color(r, max_depth, world); // Adds the orientation (color) pf the ray together
                }
                write_color(std::cout, pixel_samples_scale * pixel_color); //averages the color at that point
            }
        }

        std::clog << "\rDone.                 \n";
    }

  private:
    int    image_height;   
    point3 center;        
    point3 pixel00_loc;    
    vec3   pixel_delta_u; 
    vec3   pixel_delta_v;  
    double pixel_samples_scale; //Color factor for sum of pixels

    void initialize() {
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        pixel_samples_scale = 1.0 / samples_per_pixel;

        center = point3(0, 0, 0);

        // Determine viewport dimensions.
        auto focal_length = 1.0;
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * (double(image_width)/image_height);

        // Calculate the vectors across the horizontal and down the vertical viewport edges.
        auto viewport_u = vec3(viewport_width, 0, 0);
        auto viewport_v = vec3(0, -viewport_height, 0);

        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Calculate the location of the upper left pixel.
        auto viewport_upper_left =
            center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }
    ray get_ray(int i, int j) const {

        auto offset = sample_square();
        auto pixel_sample = pixel00_loc //generates random pixel based on offset from current pixel
                          + ((i + offset.x()) * pixel_delta_u)
                          + ((j + offset.y()) * pixel_delta_v);

        auto ray_origin = center; //Ray center at camera center 
        auto ray_direction = pixel_sample - ray_origin; //Where is the pixel? What direction is it?

        return ray(ray_origin, ray_direction);
    }

    vec3 sample_square() const {
        // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }
    color ray_color(const ray& r, int depth, const hittable& world) const {
        hit_record rec;
        //Limit number of child rays 
        if (depth <= 0){
            return color(0,0,0);
        }
        if (world.hit(r, interval(0.001, infinity), rec)) { //checks if it hits something
           vec3 direction = rec.normal + random_unit_vector(); //makes sure it on the same hemisphere
           //Rec.p is the point on the surface. Direction = the outward facing normal
           return 0.5 * ray_color(ray(rec.p, direction), depth-1, world); 
        }
        //Background color
        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5*(unit_direction.y() + 1.0);
        return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
    }
};

#endif