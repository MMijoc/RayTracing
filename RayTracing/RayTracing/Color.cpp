#include <iostream>

#include "Color.h"

namespace RayTracing {

    void WriteColor(std::ostream &out, Color pixelColor) 
    {
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(255.999 * pixelColor.X()) << ' '
        << static_cast<int>(255.999 * pixelColor.Y()) << ' '
        << static_cast<int>(255.999 * pixelColor.Z()) << '\n';
    }

}
