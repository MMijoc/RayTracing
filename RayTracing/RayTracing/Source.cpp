#include "Source.h"
#include "Camera.h"
#include "Ray.h"
#include "Vector3.h"
#include "Color.h"
#include "HittableList.h"

using namespace RayTracing;

void CreateImageFile();
Color RayColor(const Ray& ray, const Hittable& world);

int main()
{
	CreateImageFile();

	// Convert .ppm image to .png so it can easily be viewed
	// Conversion is done using ImageMagic Command-line Tools
	system("magick convert image.ppm image.png");
	return 0;
}

void CreateImageFile()
{
	std::ofstream ppmImageFile;
	ppmImageFile.open("image.ppm");

	// Image
	constexpr auto aspectRatio = 16.0 / 9.0;
	constexpr auto imageWidth = 400;
	constexpr auto imageHeight = static_cast<int>(imageWidth / aspectRatio);
	constexpr int samplesPerPixel = 100;

	// World
	HittableList world;
	world.Add(make_shared<Sphere>(Point3(0, 0, -1), 0.5));
	world.Add(make_shared<Sphere>(Point3(0, -100.5, -1), 100));

	// Camera
	Camera camera;


	// Render
	ppmImageFile << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

	for (int j = imageHeight - 1; j >= 0; --j) {
		std::cerr << "\rScan-lines remaining: " << j << ' ' << std::flush; // progress indicator
		for (int i = 0; i < imageWidth; ++i) {
			auto pixelColor = Color(0, 0, 0);
			for (int s = 0; s < samplesPerPixel; ++s)
			{
				const auto u = (i + RandomDouble()) / (imageWidth - 1);
				const auto v = (j + RandomDouble()) / (imageHeight - 1);
				Ray ray = camera.GetRay(u, v);
				pixelColor += RayColor(ray, world);
			}
			WriteColor(ppmImageFile, pixelColor, samplesPerPixel);
		}
	}
	std::cerr << "\nDone.\n";

	ppmImageFile.close();
}

Color RayColor(const Ray& ray, const Hittable& world)
{
	HitRecord record;

	if (world.Hit(ray, 0, INF, record)) {
		return 0.5 * (record.NormalVector + Color(1, 1, 1));
	}

	const Vector3 unitDirection = UnitVector(ray.GetDirection());
	const auto t = 0.5 * (unitDirection.Y() + 1.0);

	const auto startColor = Color(0.5, 0.7, 1.0);
	const auto endColor = Color(1.0, 1.0, 1.0);
	const auto resultColor = (1.0 - t) * endColor + (t * startColor);

	return resultColor;
}
