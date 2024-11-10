#ifndef GENERAL_H
#define GENERAL_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <cstdlib>


//usings
using std::make_shared;
using std::shared_ptr;

//constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

//utils
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double() {
    //random double from [0,1)
    return std::rand()/(1.0+RAND_MAX);
}

inline double random_double(double min, double max) {
    //random double from [min, max)
    return min + (max-min)*random_double();
}

//other header files
#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "interval.h"
#endif