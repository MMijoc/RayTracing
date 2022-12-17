#include <iostream>
#include <fstream>

#include "Source.h"
#include "Vector3.h"
#include "Color.h"
#include "Ray.h"

using namespace RayTracing;


int main()
{
	CreateImageFile();
	return 0;
}

void CreateImageFile()
{
	// Image
	const auto aspectRatio = 16.0 / 9.0;
	const auto imageWidth = 400;
	const auto imageHeight = static_cast<int>(imageWidth / aspectRatio);

	std::ofstream ppmImageFile;
	ppmImageFile.open("image.ppm");


	// Camera
	auto viewportHeight = 2.0;
	auto viewportWidth = aspectRatio * viewportHeight;
	auto focalLength = 1.0;

	auto origin = Point3(0, 0, 0);
	auto horizontal = Vector3(viewportWidth, 0, 0);
	auto vertical = Vector3(0, viewportHeight, 0);
	Point3 lowerLeftCorner = Vector3(-viewportWidth / 2, -viewportHeight / 2, -focalLength);


	// Render
	ppmImageFile << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

	for (int j = imageHeight - 1; j >= 0; --j) {
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush; // progress indicator
		for (int i = 0; i < imageWidth; ++i) {
			auto u = double(i) / (imageWidth - 1);
			auto v = double(j) / (imageHeight - 1);
			Ray r(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
			Color pixelColor = RayColor(r);
			WriteColor(ppmImageFile, pixelColor);
		}
	}
	std::cerr << "\nDone.\n";

	ppmImageFile.close();
}

Color RayColor(const Ray& ray)
{
	Point3 sphereCenter = Point3(0, 0, 1);
	double sphereRadius = 0.5;
	Color sphereColor = Color(1, 0, 0);

	if (IsSphereHit(sphereCenter, sphereRadius, ray))
		return sphereColor;

	Vector3 unitDirection = UnitVector(ray.GetDirection());
	double t = 0.5 * (unitDirection.Y() + 1.0); // we scale t between 0 and 1
	Color startColor = Color(0, 0.46, 0.72);
	Color endColor = Color(0.0, 1.0, 0.0);
	auto rayColor = (1.0 - t) * endColor + (t * startColor);

	return rayColor;
}

bool IsSphereHit(const Point3& center, double radius, const Ray& ray)
{
	Vector3 oc = ray.GetOrigin() - center;
	auto a = Dot(ray.GetDirection(), ray.GetDirection());
	auto b = 2.0 * Dot(oc, ray.GetDirection());
	auto c = Dot(oc, oc) - radius * radius;
	auto discriminant = b * b - 4 * a * c;

	return (discriminant > 0);
}