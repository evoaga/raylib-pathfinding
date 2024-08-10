#pragma once

#include "raylib.h"
#include "VectorMath.hpp"
#include <vector>
#include <random>
#include "ThetaStar.hpp"
#include "Components/Components.hpp"

Color GetRandomColor();
Point vector3ToPoint(const Vector3 &vec);
Polygon generateCubePolygon(const TransformComponent &transform);
bool CheckCollisionAABB(Vector3 position, Vector3 scale, Vector3 obstaclePos, Vector3 obstacleScale);
Vector3 GetMousePosition3D(Camera3D camera);
bool CheckCollisionSegmentBox(Vector3 start, Vector3 end, BoundingBox box);
