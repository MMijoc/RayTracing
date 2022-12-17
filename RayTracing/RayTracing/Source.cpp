#include <iostream>
#include <fstream>

#include "Source.h"
#include "Vector3.h"
#include "Color.h"
#include "Ray.h"

using namespace RayTracing;
Color RayColor(const Ray& ray);
bool HitSphere(const Point3& center, double radius, const Ray& ray);


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
	//auto lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - Vector3(0, 0, focalLength);
	Point3 lowerLeftCorner = Vector3(-viewportWidth / 2, -viewportHeight / 2, -focalLength);


	// Render
	ppmImageFile << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

	for (int j = imageHeight - 1; j >= 0; --j) {
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush; // progress indicator
		for (int i = 0; i < imageWidth; ++i) {
			//Color pixelColor(double(i) / (imageWidth - 1), double(j) / (imageHeight - 1), 0.25);
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

Color RayColor(const Ray& ray) {

	Point3 sphereCenter = Point3(0, 0, 1);
	double sphereRadius = 0.5;

	if (HitSphere(sphereCenter, sphereRadius, ray))
		return Color(1, 0, 0);

	Vector3 unitDirection = UnitVector(ray.GetDirection()); // Unit vector of direction
	double t = 0.5 * (unitDirection.Y() + 1.0); // we scale t betweene 0 and 1, t depends on y axis of vector direction
	// blendedValue = (1−t)*startValue + t*endValue <- linar interpolation
	//              multiplyer * endColor            multiplyer * start color            
	auto rayColor = (1.0 - t) * Color(0.0, 1.0, 0.0) + t * Color(0.5, 0.7, 1.0);
	return rayColor;
}

bool HitSphere(const Point3& center, double radius, const Ray& ray) {
	Vector3 oc = ray.GetOrigin() - center;
	auto a = Dot(ray.GetDirection(), ray.GetDirection());
	auto b = 2.0 * Dot(oc, ray.GetDirection());
	auto c = Dot(oc, oc) - radius*radius;
	auto discriminant = b*b - 4*a*c;
	return (discriminant > 0);
}