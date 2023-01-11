#include "Source.h"
#include "Camera.h"
#include "Ray.h"
#include "Vector3.h"
#include "Color.h"
#include "HittableList.h"
#include "Material.h"
#include "RayTracing.h"

using namespace RayTracing;

void CreateImageFile();
Color RayColor(const Ray& ray, const Hittable& world, int depth);

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
	constexpr int maxDepth = 50;

	// World
	HittableList world;

	auto materialGround = make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
	auto materialCenter = make_shared<Lambertian>(Color(0.7, 0.3, 0.3));
	auto materialLeft   = make_shared<Metal>(Color(0.8, 0.8, 0.8), 0.3);
	auto materialRight  = make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);

	world.Add(make_shared<Sphere>(Point3( 0.0, -100.5, -1.0), 100.0, materialGround));
	world.Add(make_shared<Sphere>(Point3( 0.0,    0.0, -1.0),   0.5, materialCenter));
	world.Add(make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),   0.5, materialLeft));
	world.Add(make_shared<Sphere>(Point3( 1.0,    0.0, -1.0),   0.5, materialRight));


	// Camera
	const Camera camera;


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
				pixelColor += RayColor(ray, world, maxDepth);
			}
			WriteColor(ppmImageFile, pixelColor, samplesPerPixel);
		}
	}
	std::cerr << "\nDone.\n";

	ppmImageFile.close();
}

Color RayColor(const Ray& ray, const Hittable& world, const int depth)
{
	HitRecord hitRecord;

	// If we've exceeded the ray bounce limit, no more light is gathered.
	if (depth <= 0)
		return Color(0, 0, 0);

	if (world.Hit(ray, 0.001, INF, hitRecord)) {
		//const Point3 target = hitRecord.Point + hitRecord.NormalVector + RandomUnitVector();
		//const Point3 target = hitRecord.Point + RandomInHemisphere(hitRecord.NormalVector);
		Ray scatteredRay;
		Color attenuation;
		if (hitRecord.MaterialPtr->Scatter(ray, hitRecord, attenuation, scatteredRay))
			return attenuation * RayColor(scatteredRay, world, depth - 1);

		return Color(0, 0, 0);

		//return 0.5 * RayColor(Ray(hitRecord.Point, target - hitRecord.Point), world, depth - 1);
	}

	const Vector3 unitDirection = UnitVector(ray.GetDirection());
	const auto t = 0.5 * (unitDirection.Y() + 1.0);

	const auto startColor = Color(0.5, 0.7, 1.0);
	const auto endColor = Color(1.0, 1.0, 1.0);
	const auto resultColor = (1.0 - t) * endColor + (t * startColor);

	return resultColor;
}
