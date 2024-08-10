#pragma once

#include "Components/Components.hpp"
#include "ThetaStar.hpp"
#include "raylib.h"
#include <vector>

bool isPointInPolygon(const Point &point, const std::vector<Point> &polygon);
bool isPointInAnyPolygon(const Vector3 &point, const std::vector<Polygon> &polygons);
bool lineIntersectsPolygon(const Point &pStart, const Point &pEnd, const Polygon &polygon);
bool lineIntersectsPolygonLoS(const Point &pStart, const Point &pEnd, const Polygon &polygon);
Vector3 findNearestValidPoint(const Vector3 &point, const std::vector<Polygon> &polygons, float buffer);
Point calculateCentroid(const Polygon &polygon);
float calculateAngle(const Point &center, const Point &point);
void sortPolygonClockwise(Polygon &polygon);