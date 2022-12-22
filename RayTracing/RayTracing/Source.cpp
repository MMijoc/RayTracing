#include "Source.h"

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
	std::ofstream ppmImageFile;
	ppmImageFile.open("image.ppm");

	// Image
	const auto aspectRatio = 16.0 / 9.0;
	const auto imageWidth = 400;
	const auto imageHeight = static_cast<int>(imageWidth / aspectRatio);

	// World


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
		std::cerr << "\rScan-lines remaining: " << j << ' ' << std::flush; // progress indicator
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
	Vector3 oc = ray.GetOrigin() - sphereCenter;
	auto a = ray.GetDirection().LengthSquared();
	auto bHalf = Dot(oc, ray.GetDirection());
	auto c = oc.LengthSquared() - sphereRadius * sphereRadius;
	auto discriminant = bHalf * bHalf -  a * c;

	if (discriminant < 0) {
		// No real solutions
		return -1.0;
	} else {
		double t1 =  (-bHalf - sqrt(discriminant)) / a;
		return t1;
	}
}