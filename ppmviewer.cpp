#include <iostream>

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
            auto r = double(i)/maxColor;
            auto g = double(j)/maxColor;
            auto b = 0.0;

            //scale the rgb values for printing to ppm
            int ir = int(255.999 * r);
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);

            std::cout << ir << " " << ig << " " << ib << "\n"; 
        }
    }
    std::clog << "\rdone! :D      \n";
}