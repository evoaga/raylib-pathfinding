#ifndef UTILS_HPP
#define UTILS_HPP

#include "raylib.h"
#include "VectorMath.hpp"
#include "GameObject.hpp"
#include <vector>
#include <random>

Vector3 GetMousePosition3D(Camera3D camera);
bool CheckCollisionSegmentBox(Vector3 start, Vector3 end, BoundingBox box);

#endif // UTILS_HPP

