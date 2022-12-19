#include <iostream>
#include <fstream>

#include "Vector3.h"
#include "Color.h"
#include "Ray.h"


using namespace RayTracing;

void CreateImageFile();
Color RayColor(const Ray& ray);
double HitSphere(const Point3& center, double radius, const Ray& ray);

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
			Point3 currentDirection = lowerLeftCorner + u * horizontal + v * vertical - origin;
			Ray r(origin,currentDirection);
			Vector3 pixelColor = RayColor(r);
			WriteColor(ppmImageFile, pixelColor);
		}
	}
	std::cerr << "\nDone.\n";

	ppmImageFile.close();
}

Color RayColor(const Ray& ray)
{
	Point3 sphereCenter = Point3(0, 0, -1);
	double sphereRadius = 0.5;
	double t = HitSphere(sphereCenter, sphereRadius, ray);
	bool rayHitsSphere = t > 0;

	// Normal vectors color map
	if (rayHitsSphere) {
		Vector3 normalVector = UnitVector(ray.At(t) - sphereCenter);
		Color normalVectorColor = 0.5 * Color(normalVector.X() + 1, normalVector.Y() + 1, normalVector.Z() + 1);
		return normalVectorColor;
	}

	Vector3 unitDirection = UnitVector(ray.GetDirection());
	t = 0.5 * (unitDirection.Y() + 1.0); // we scale t between 0 and 1
	Color startColor = Color(0, 0.46, 0.72);
	Color endColor = Color(0.0, 1.0, 0.0);
	auto backgroundColor = (1.0 - t) * endColor + (t * startColor);

	return backgroundColor;
}

double HitSphere(const Point3& sphereCenter, double sphereRadius, const Ray& ray)
{
	// Sphere equation (in vector form):
	// (A + tB - C)^2 - r^2 = 0
	// b*b*(t^2) + (A-C)*2B*(t) + (A-C)(A-C)-r^2 = 0
	//
	// a = b*b
	// b = (A-C)*2*B
	// c = (A-C)(A-C)-r^2
	// Solve for t using quadratic equation
	// if t>=0 the ray did hit the sphere
	Vector3 oc = ray.GetOrigin() - sphereCenter;
	auto a = Dot(ray.GetDirection(), ray.GetDirection());
	auto b = 2.0 * Dot(oc, ray.GetDirection());
	auto c = Dot(oc, oc) - sphereRadius * sphereRadius;
	auto discriminant = b * b - 4 * a * c;

	if (discriminant < 0) {
		// No real solutions
		return -1;
	} else {
		double t1 =  (-b - sqrt(discriminant)) / (2.0 * a);
		//double t2 =  (-b + sqrt(discriminant)) / (2.0 * a);
		return t1;
	}
}