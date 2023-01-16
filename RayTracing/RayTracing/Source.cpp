#include "Source.h"

using namespace RayTracing;

void CreateImageFile();
Color RayColor(const Ray& ray, const Hittable& world, int depth);
void WriteColor(std::ostream& out, const Color pixelColor, const int samplesPerPixel);
HittableList GenerateComplexWorldScene();
HittableList GenerateSimpleWorldScene();


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
	constexpr int samplesPerPixel = 5;
	constexpr int maxDepth = 25;

	// World
	// COMPLEX
	//const auto world = GenerateComplexWorldScene();

	// SIMPLE
	const auto world = GenerateSimpleWorldScene();

	// Camera

	const auto lookFrom = Point3(13, 2, 3);
	const auto lookAt = Point3(0, 0, 0);
	const auto viewUp = Vector3(0, 1, 0);
	constexpr auto distanceToFocus = 10.0;
	constexpr auto aperture = 0.1;
	constexpr auto verticalFiledOfView = 20.0;
	const Camera camera(lookFrom, lookAt, viewUp, verticalFiledOfView, aspectRatio, aperture, distanceToFocus);

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

HittableList GenerateComplexWorldScene()
{
	HittableList world;

	auto groundMaterial = make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
	world.Add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, groundMaterial));

	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			const auto chooseMaterialChance = RandomDouble();
			Point3 center(a + 0.9 * RandomDouble(), 0.2, b + 0.9 * RandomDouble());

			if ((center - Point3(4, 0.2, 0)).Length() > 0.9) {
				shared_ptr<Material> sphereMaterial;

				if (chooseMaterialChance < 0.8) {
					// diffuse
					auto albedo = Color::Random() * Color::Random();
					sphereMaterial = make_shared<Lambertian>(albedo);
					world.Add(make_shared<Sphere>(center, 0.2, sphereMaterial));
				} else if (chooseMaterialChance < 0.95) {
					// metal
					auto albedo = Color::Random(0.5, 1);
					auto fuzz = RandomDouble(0, 0.5);
					sphereMaterial = make_shared<Metal>(albedo, fuzz);
					world.Add(make_shared<Sphere>(center, 0.2, sphereMaterial));
				} else {
					// glass
					sphereMaterial = make_shared<Dielectric>(1.5);
					world.Add(make_shared<Sphere>(center, 0.2, sphereMaterial));
				}
			}
		}
	}

	auto material1 = make_shared<Dielectric>(1.5);
	world.Add(make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

	auto material2 = make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
	world.Add(make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

	auto material3 = make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
	world.Add(make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

	return world;
}

HittableList GenerateSimpleWorldScene()
{
	HittableList world;

	auto materialGround = make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
	auto materialCenter = make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
	auto materialLeft   = make_shared<Dielectric>(1.5);
	auto materialRight  = make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.0);

	world.Add(make_shared<Sphere>(Point3( 0.0, -100.5, -1.0), 100.0, materialGround));
	world.Add(make_shared<Sphere>(Point3( 0.0,    0.0, -1.0),   0.5, materialCenter));
	world.Add(make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),   0.5, materialLeft));
	world.Add(make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),  -0.4, materialLeft));
	world.Add(make_shared<Sphere>(Point3( 1.0,    0.0, -1.0),   0.5, materialRight));

	return world;
}


void WriteColor(std::ostream &out, const Color pixelColor, const int samplesPerPixel) 
{
	auto r = pixelColor.X();
	auto g = pixelColor.Y();
	auto b = pixelColor.Z();

	// Multisample anti-aliasing
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


