#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

using color = vec3;

void write_color(std::ostream& out, const color& pixel_color) {
    //extract color values (these are in range [0,1])
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    //map color values to [0,255] ie byte range
    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    //write byte colors to out
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
    

}
#endif