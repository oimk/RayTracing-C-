#ifndef COLOR_H
#define COLOR_H
#include "vec3.h"
#include "interval.h"

using color = vec3;

inline double linear_to_gamma(double linear_componenet){
    if (linear_componenet > 0)
        return std::sqrt(linear_componenet);
    return 0;
}

void write_color(std::ostream& out, const color& pixel_color){
    //Cordinates of the vector is the color 
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Apply a linear to gamma transform for gamma 2
    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    //Translates the [0,1] component values to the byte range [0,255]
    static const interval intensity (0.000, 0.999);
    int rbyte = int(255.999 * intensity.clamp(r));
    int gbyte = int(255.999 * intensity.clamp(g));
    int bbyte = int(255.999 * intensity.clamp(b));

    //Write out color components 
    out << rbyte << " " << gbyte << " " << bbyte << " " << "\n";
}
#endif