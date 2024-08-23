#include <cstdlib>
#include <vector>
#include <cmath>
#include <utility>
#include "Utils.hpp"

#include "Components.hpp"
#include "ThetaStar.hpp"
#include "VectorMath.hpp"
#include "raylib.h"

auto GetRandomColor() -> Color
{
    return Color {
        static_cast<unsigned char>(rand() % 256),  // Red component
        static_cast<unsigned char>(rand() % 256),  // Green component
        static_cast<unsigned char>(rand() % 256),  // Blue component
        255  // Alpha component
    };
}

auto vector3ToPoint(const Vector3 &vec) -> Point
{
    return Point {vec.x, vec.y, vec.z};
}

auto generateCubePolygon(const TransformComponent &transform) -> Polygon
{
    std::vector<Point> points;
    const float buffer = 0.5F + 0.0001F;
    const Vector3 &pos = transform.position;
    const Vector3 &rot = transform.rotation;
    const Vector3 &scale = transform.scale;

    std::vector<Vector3> const localVertices = {
        {-scale.x / 2 - buffer, 0.0F, -scale.z / 2 - buffer},
        {-scale.x / 2 - buffer, 0.0F, scale.z / 2 + buffer},
        {scale.x / 2 + buffer, 0.0F, scale.z / 2 + buffer},
        {scale.x / 2 + buffer, 0.0F, -scale.z / 2 - buffer},
    };

    for (const auto &vertex : localVertices) {
        float const rotatedX = cos(rot.y) * vertex.x - sin(rot.y) * vertex.z;
        float const rotatedZ = sin(rot.y) * vertex.x + cos(rot.y) * vertex.z;
        points.emplace_back(pos.x + rotatedX, 0.0F, pos.z + rotatedZ);
    }

    return Polygon {points};
}

auto CheckCollisionAABB(Vector3 position,
                        Vector3 scale,
                        Vector3 obstaclePos,
                        Vector3 obstacleScale) -> bool
{
    return (fabs(position.x - obstaclePos.x) * 2 < (scale.x + obstacleScale.x))
        && (fabs(position.y - obstaclePos.y) * 2 < (scale.y + obstacleScale.y))
        && (fabs(position.z - obstaclePos.z) * 2 < (scale.z + obstacleScale.z));
}

auto GetMousePosition3D(Camera3D camera) -> Vector3
{
    Vector2 const mousePosition = GetMousePosition();
    Ray const ray = GetMouseRay(mousePosition, camera);

    // Calculate the point on the ground plane (y = 0)
    float const t = -ray.position.y / ray.direction.y;
    Vector3 mousePosition3D = Vector3Add(ray.position, Vector3Scale(ray.direction, t));

    return mousePosition3D;
}

// Function to check if a line segment intersects with a bounding box
auto CheckCollisionSegmentBox(Vector3 start, Vector3 end, BoundingBox box) -> bool
{
    Vector3 const d = Vector3Subtract(end, start);

    float tmin = (box.min.x - start.x) / d.x;
    float tmax = (box.max.x - start.x) / d.x;

    if (tmin > tmax) {
        std::swap(tmin, tmax);
    }

    float tymin = (box.min.z - start.z) / d.z;
    float tymax = (box.max.z - start.z) / d.z;

    if (tymin > tymax) {
        std::swap(tymin, tymax);
    }

    if ((tmin > tymax) || (tymin > tmax)) {
        return false;
    }

    if (tymin > tmin) {
        tmin = tymin;
    }

    if (tymax < tmax) {
        tmax = tymax;
    }

    return tmax >= 0.0F && tmin <= 1.0F;
}
