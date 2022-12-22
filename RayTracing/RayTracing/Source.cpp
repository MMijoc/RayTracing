#include "Source.h"

using namespace RayTracing;

void CreateImageFile();
Color RayColor(const Ray& ray, const Hittable& world);

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
	HittableList world;
	world.Add(make_shared<Sphere>(Point3(0, 0, -1), 0.5));
	world.Add(make_shared<Sphere>(Point3(0, -100.5, -1), 100));

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
			Vector3 pixelColor = RayColor(r, world);
			WriteColor(ppmImageFile, pixelColor);
		}
	}
	std::cerr << "\nDone.\n";

	ppmImageFile.close();
}

Color RayColor(const Ray& ray, const Hittable& world)
{
	HitRecord record;

	if (world.Hit(ray, 0, INF, record)) {
		return 0.5 * (record.normalVector + Color(1, 1, 1));
	}

	Vector3 unitDirection = UnitVector(ray.GetDirection());
	auto t = 0.5 * (unitDirection.Y() + 1.0);

	Color startColor = Color(0.5, 0.7, 1.0);
	Color endColor = Color(1.0, 1.0, 1.0);
	auto resultColor = (1.0 - t) * endColor + (t * startColor);

	return resultColor;
}