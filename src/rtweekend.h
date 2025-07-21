#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <iostream>
#include <limits>
#include <cstdlib>
#include <memory>

// C++
using std::make_shared;
using std::shared_ptr;

//Constants 
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

//Utility functions 

inline double degrees_to_radians(double degrees) {
    return degrees * pi /180;
}

inline double random_double() {
    return std::rand() / (RAND_MAX + 1.0); //Return [0,1)
}
inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}

//Common headers
#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "interval.h"

#endif