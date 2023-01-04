#include "Color.h"
#include "RayTracing.h"

namespace RayTracing {

    void WriteColor(std::ostream &out, const Color pixelColor, const int samplesPerPixel) 
    {
        auto r = pixelColor.X();
        auto g = pixelColor.Y();
        auto b = pixelColor.Z();

        // Divide the color by the number of samples.
        // sqrt is used to gamma-correct (gamma 2.0)
        const auto scale = 1.0 / samplesPerPixel;
        r = sqrt(scale * r);
        g = sqrt(scale * g);
        b = sqrt(scale * b);

        // Write the translated [0,255] value of each color component.
        out << static_cast<int>(256 * Clamp(r, 0.0, 0.999)) << ' '
            << static_cast<int>(256 * Clamp(g, 0.0, 0.999)) << ' '
            << static_cast<int>(256 * Clamp(b, 0.0, 0.999)) << '\n';
    }

}
