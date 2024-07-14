#ifndef UTILS_HPP
#define UTILS_HPP

#include "raylib.h"
#include "vector_math.hpp"
#include <vector>
#include <random>

Vector3 GetMousePosition3D(Camera3D camera);
bool CheckCollisionSegmentBox(Vector3 start, Vector3 end, BoundingBox box);
bool segmentIntersectsObstacle(Vector3 start, Vector3 end, const Vector3& obstacle, float obstacleSize);
std::vector<Vector3> generateObstaclePositions(int count, float mapSize);

#endif // UTILS_HPP

