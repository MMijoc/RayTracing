#pragma once

#include "Vector3.h"

namespace RayTracing {
	void WriteColor(std::ostream& out, Color pixelColor, int samplesPerPixel);
}