#pragma once

#include <random>
#include <vector>

#include "Components/Components.hpp"
#include "ThetaStar.hpp"
#include "raylib.h"

auto GetRandomColor() -> Color;
auto vector3ToPoint(const Vector3 &vec) -> Point;
auto generateCubePolygon(const TransformComponent &transform) -> Polygon;
auto CheckCollisionAABB(Vector3 position,
                        Vector3 scale,
                        Vector3 obstaclePos,
                        Vector3 obstacleScale) -> bool;
auto GetMousePosition3D(Camera3D camera) -> Vector3;
auto CheckCollisionSegmentBox(Vector3 start, Vector3 end, BoundingBox box) -> bool;