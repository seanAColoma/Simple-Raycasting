#include <iostream>
#include "color.h"
#include "vec3.h"

int main() {
    int img_width = 256;
    int img_height = 256;
    int maxColor = 255;
    
    //P3 (header)
    //256, 256 (image dimensions)
    //255 (maximum color intensity)
    std::cout << "P3\n" << img_width << " " << img_height << "\n" << maxColor << "\n";

    //image values
    for(int j = 0; j<img_height; j++){
        //progress reporting
        std::clog << "\rScanlines Remaining: " << (img_height - 1) << ' ' << std::flush;
        for(int i = 0; i<img_width; i++){
            color pixel_color = color(double(i)/(img_width-1), double(j)/(img_height-1), 0);
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\rdone! :D      \n";
}