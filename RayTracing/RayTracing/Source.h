#pragma once

#include <iostream>
#include <fstream>
#include <cmath>
#include <limits>
#include <memory>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const double INF = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;


inline double DegreesToRadians(double degrees) {
    return degrees * PI / 180.0;
}

#include "Ray.h"
#include "Vector3.h"
#include "Color.h"
#include "HittableList.h"