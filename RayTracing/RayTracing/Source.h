#pragma once

void CreateImageFile();
Color RayColor(const Ray& ray);
bool IsSphereHit(const Point3& center, double radius, const Ray& ray);