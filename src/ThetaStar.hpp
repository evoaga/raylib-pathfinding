#pragma once

#include "raylib.h"
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include <limits>
#include <cfloat>
#include "VectorMath.hpp"
#include <utility>

struct Point
{
    float x, y, z;

    Point(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

    bool operator==(const Point &other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }

    bool operator!=(const Point &other) const
    {
        return !(*this == other);
    }
};

struct Polygon
{
    std::vector<Point> vertices;
};

// Hash function for Point to use in unordered_map
struct PointHash
{
    std::size_t operator()(const Point &p) const
    {
        std::size_t h1 = std::hash<float>{}(p.x);
        std::size_t h2 = std::hash<float>{}(p.y);
        std::size_t h3 = std::hash<float>{}(p.z);
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

struct NavMesh
{
    std::vector<Point> vertices;

    void addVertex(const Point &p)
    {
        vertices.push_back(p);
    }

    void removeVertex(const Point &p)
    {
        vertices.erase(std::remove(vertices.begin(), vertices.end(), p), vertices.end());
    }

    void clear()
    {
        vertices.clear();
    }
};

struct Node
{
    Point point;
    float gCost;
    float fCost;

    Node(Point point, float gCost, float fCost)
        : point(point), gCost(gCost), fCost(fCost) {}

    bool operator>(const Node &other) const
    {
        return fCost > other.fCost;
    }
};

auto heuristic(const Point &p1, const Point &p2) -> float;
auto lineOfSight(const Point &s, const Point &sPrime, const std::vector<Polygon> &polygons) -> bool;
auto thetaStar(NavMesh &mesh, const Point &start, const Point &goal, const std::vector<Polygon> &obstaclePolygons) -> std::vector<Point>;