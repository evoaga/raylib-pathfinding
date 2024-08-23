
#include "Polygons.hpp"

#include "ThetaStar.hpp"
#include "VectorMath.hpp"
#include "raylib.h"

// Point-in-Polygon Test using Ray-Casting algorithm
auto isPointInPolygon(const Point &point, const std::vector<Point> &polygon) -> bool
{
    size_t const n = polygon.size();
    int crossings = 0;
    for (size_t i = 0; i < n; i++) {
        const Point &p1 = polygon[i];
        const Point &p2 = polygon[(i + 1) % n];
        if (((p1.z > point.z) != (p2.z > point.z))
            && (point.x < (p2.x - p1.x) * (point.z - p1.z) / (p2.z - p1.z) + p1.x))
        {
            crossings++;
        }
    }
    return (crossings % 2) != 0;
}

auto isPointInAnyPolygon(const Vector3 &point, const std::vector<Polygon> &polygons) -> bool
{
    Point const pointPos = {point.x, 0.0F, point.z};

    for (const auto &polygon : polygons) {
        if (isPointInPolygon(pointPos, polygon.vertices)) {
            return true;
        }
    }
    return false;
}

auto closestPointOnLineSegment(const Vector3 &p, const Vector3 &a, const Vector3 &b) -> Vector3
{
    Vector3 const ab = Vector3Subtract(b, a);
    float t = Vector3DotProduct(Vector3Subtract(p, a), ab) / Vector3DotProduct(ab, ab);
    t = std::max(0.0F, std::min(1.0F, t));
    return Vector3Add(a, Vector3Scale(ab, t));
}

auto direction(const Point &p, const Point &q, const Point &r) -> float
{
    return (q.x - p.x) * (r.z - p.z) - (q.z - p.z) * (r.x - p.x);
}

auto onSegment(const Point &p, const Point &q, const Point &r) -> bool
{
    return (r.x >= std::min(p.x, q.x) && r.x <= std::max(p.x, q.x) && r.z >= std::min(p.z, q.z)
            && r.z <= std::max(p.z, q.z));
}

auto doLinesIntersect(const Point &p1, const Point &p2, const Point &q1, const Point &q2) -> bool
{
    float const d1 = direction(q1, q2, p1);
    float const d2 = direction(q1, q2, p2);
    float const d3 = direction(p1, p2, q1);
    float const d4 = direction(p1, p2, q2);

    if (d1 * d2 < 0 && d3 * d4 < 0) {
        return true;
    }

    if (d1 == 0 && onSegment(q1, q2, p1)) {
        return true;
    }
    if (d2 == 0 && onSegment(q1, q2, p2)) {
        return true;
    }
    if (d3 == 0 && onSegment(p1, p2, q1)) {
        return true;
    }
    if (d4 == 0 && onSegment(p1, p2, q2)) {
        return true;
    }

    return false;
}

auto lineIntersectsPolygon(const Point &pStart, const Point &pEnd, const Polygon &polygon) -> bool
{
    size_t const n = polygon.vertices.size();

    for (size_t i = 0; i < n; ++i) {
        size_t const next_i = (i + 1) % n;
        const Point &v1 = polygon.vertices[i];
        const Point &v2 = polygon.vertices[next_i];

        if (doLinesIntersect(pStart, pEnd, v1, v2)) {
            return true;
        }
    }
    return false;
}

auto lineIntersectsPolygonLoS(const Point &pStart,
                              const Point &pEnd,
                              const Polygon &polygon) -> bool
{
    size_t const n = polygon.vertices.size();
    bool startOnEdge = false;
    size_t startEdgeIndex = 0;
    bool startIsVertex = false;
    bool endIsVertex = false;
    size_t startIndex = 0;
    size_t endIndex = 0;

    // Check if start and end points are vertices of the polygon
    for (size_t i = 0; i < n; ++i) {
        if (polygon.vertices[i].x == pStart.x && polygon.vertices[i].z == pStart.z) {
            startIsVertex = true;
            startIndex = i;
        }
        if (polygon.vertices[i].x == pEnd.x && polygon.vertices[i].z == pEnd.z) {
            endIsVertex = true;
            endIndex = i;
        }
    }

    // Check if both points are vertices and not neighbors
    if (startIsVertex && endIsVertex) {
        if ((startIndex + 1) % n != endIndex && startIndex != (endIndex + 1) % n) {
            return true;
        }
    }

    // Check if pStart is on an edge of the polygon but not a vertex
    for (size_t i = 0; i < n; ++i) {
        size_t const next_i = (i + 1) % n;
        Point const v1 = polygon.vertices[i];
        Point const v2 = polygon.vertices[next_i];

        if (onSegment(v1, v2, pStart) && !(pStart == v1 || pStart == v2)) {
            startOnEdge = true;
            startEdgeIndex = i;
            break;
        }
    }

    if (startOnEdge) {
        // Check if pEnd is a vertex
        if (endIsVertex) {
            size_t const next_index = (startEdgeIndex + 1) % n;
            if (endIndex == startEdgeIndex || endIndex == next_index) {
                return false;  // pStart and pEnd are on the same edge
            }
        }

        // Otherwise, check for any edge intersection
        for (size_t i = 0; i < n; ++i) {
            if (i == startEdgeIndex) {
                continue;  // Skip the edge that contains pStart
            }

            size_t const next_i = (i + 1) % n;
            Point const v1 = polygon.vertices[i];
            Point const v2 = polygon.vertices[next_i];

            if (doLinesIntersect(pStart, pEnd, v1, v2)) {
                return true;
            }
        }
        return false;
    }

    // Check if the line intersects with any of the polygon's edges
    for (size_t i = 0; i < n; ++i) {
        size_t const next_i = (i + 1) % n;
        Point const v1 = polygon.vertices[i];
        Point const v2 = polygon.vertices[next_i];

        // Skip this edge if pStart or pEnd is exactly on one of the vertices of the polygon
        if (pStart == v1 || pStart == v2 || pEnd == v1 || pEnd == v2) {
            continue;
        }

        if (doLinesIntersect(pStart, pEnd, v1, v2)) {
            return true;
        }
    }
    return false;
}

auto findNearestValidPoint(const Vector3 &point,
                           const std::vector<Polygon> &polygons,
                           float buffer) -> Vector3
{
    Vector3 nearestPoint = point;
    float minDistance = FLT_MAX;

    for (const auto &polygon : polygons) {
        for (size_t i = 0; i < polygon.vertices.size(); ++i) {
            const Point &v1 = polygon.vertices[i];
            const Point &v2 = polygon.vertices[(i + 1) % polygon.vertices.size()];

            Vector3 const edgePoint = closestPointOnLineSegment(
                point, Vector3 {v1.x, point.y, v1.z}, Vector3 {v2.x, point.y, v2.z});
            Vector3 const bufferedPoint = Vector3Add(
                edgePoint,
                Vector3Scale(
                    Vector3Normalize(Vector3Subtract(
                        edgePoint, Vector3 {(v1.x + v2.x) / 2, point.y, (v1.z + v2.z) / 2})),
                    buffer));

            if (!isPointInAnyPolygon(bufferedPoint, polygons)) {
                float const distance = Vector3Distance(point, bufferedPoint);
                if (distance < minDistance) {
                    minDistance = distance;
                    nearestPoint = bufferedPoint;
                }
            }
        }
    }

    return nearestPoint;
}

// Helper function to calculate the centroid of a polygon
auto calculateCentroid(const Polygon &polygon) -> Point
{
    Point centroid = {0, 0, 0};
    for (const auto &vertex : polygon.vertices) {
        centroid.x += vertex.x;
        centroid.y += vertex.y;
        centroid.z += vertex.z;
    }
    auto const n = static_cast<float>(polygon.vertices.size());
    centroid.x /= n;
    centroid.y /= n;
    centroid.z /= n;
    return centroid;
}

// Helper function to calculate the angle between two points
auto calculateAngle(const Point &center, const Point &point) -> float
{
    return std::atan2(point.z - center.z, point.x - center.x);
}

// Function to sort polygon vertices in clockwise order
auto sortPolygonClockwise(Polygon &polygon) -> void
{
    Point centroid = calculateCentroid(polygon);
    std::sort(polygon.vertices.begin(),
              polygon.vertices.end(),
              [&centroid](const Point &a, const Point &b)
              { return calculateAngle(centroid, a) > calculateAngle(centroid, b); });
}
