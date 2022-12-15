#include <iostream>
#include <fstream>

#include "Source.h"
#include "Vector3.h"
#include "Color.h"

using namespace RayTracing;

int main()
{
	CreateImageFile();

	return 0;
}

void CreateImageFile()
{
	// Image
	const int imageWidth = 256;
	const int imageHeight = 256;

	std::ofstream ppmImageFile;
	ppmImageFile.open("image.ppm");

	// Render
	ppmImageFile << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

	for (int j = imageHeight - 1; j >= 0; --j) {
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush; // progress indicator
		for (int i = 0; i < imageWidth; ++i) {
			Color pixel_color(double(i) / (imageWidth - 1), double(j) / (imageHeight - 1), 0.25);
			WriteColor(ppmImageFile, pixel_color);
		}
	}
	std::cerr << "\nDone.\n";

	ppmImageFile.close();
}