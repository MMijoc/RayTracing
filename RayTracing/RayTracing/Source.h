#pragma once

#include <iostream>
#include <fstream>
#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const double INF = std::numeric_limits<double>::infinity();
constexpr double PI = 3.1415926535897932385;


inline double DegreesToRadians(const double degrees) {
	return degrees * PI / 180.0;
}

inline double RandomDouble() {
	// Returns a random real in [0,1).
	return rand() / (RAND_MAX + 1.0);
}

inline double RandomDouble(const double min, const double max) {
	// Returns a random real in [min,max).
	return min + (max - min) * RandomDouble();
}

inline double Clamp(const double x, const double min, const double max)
{
	if (x < min) return min;
	if (x > max) return max;
	return x;
}