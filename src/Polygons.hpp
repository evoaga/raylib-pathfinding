#pragma once

#include "ThetaStar.hpp"
#include "raylib.h"

auto isPointInPolygon(const Point &point, const std::vector<Point> &polygon) -> bool;
auto isPointInAnyPolygon(const Vector3 &point, const std::vector<Polygon> &polygons) -> bool;
auto lineIntersectsPolygon(const Point &pStart, const Point &pEnd, const Polygon &polygon) -> bool;
auto lineIntersectsPolygonLoS(const Point &pStart, const Point &pEnd, const Polygon &polygon) -> bool;
auto findNearestValidPoint(const Vector3 &point, const std::vector<Polygon> &polygons, float buffer) -> Vector3;
auto calculateCentroid(const Polygon &polygon) -> Point;
auto calculateAngle(const Point &center, const Point &point) -> float;
void sortPolygonClockwise(Polygon &polygon);