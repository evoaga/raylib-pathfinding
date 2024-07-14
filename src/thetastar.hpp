#ifndef THETASTAR_HPP
#define THETASTAR_HPP

#include "raylib.h"
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include <limits>
#include <cfloat>
#include "vector_math.hpp"
#include "utils.hpp"

struct Point {
    float x, y, z;

    Point(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y && z == other.z;
    }
};

// Hash function for Point to use in unordered_map
struct PointHash {
    std::size_t operator()(const Point& p) const {
        return std::hash<float>()(p.x) ^ std::hash<float>()(p.y) ^ std::hash<float>()(p.z);
    }
};

// Edge connecting two points
struct Edge {
    Point p1, p2;
    float cost;

    Edge(Point p1, Point p2, float cost) : p1(p1), p2(p2), cost(cost) {}
};

class NavMesh {
public:
    std::vector<Point> vertices;
    std::vector<Edge> edges;

    void addVertex(const Point& p);
    void addEdge(const Point& p1, const Point& p2, float cost);
    void clear();
};

float heuristic(const Point& p1, const Point& p2);

struct Node {
    Point point;
    float gCost;
    float fCost;

    Node(Point point, float gCost, float fCost)
        : point(point), gCost(gCost), fCost(fCost) {}

    bool operator>(const Node& other) const {
        return fCost > other.fCost;
    }
};

bool lineOfSight(const Point& s, const Point& sPrime, const std::vector<Vector3>& obstaclePositions, float obstacleSize);

std::vector<Point> thetaStar(const NavMesh& mesh, const Point& start, const Point& goal, const std::vector<Vector3>& obstaclePositions, float obstacleSize);

bool isPointInsideObstacle(const Point& point, const Vector3& obstacle, float obstacleSize);

Point findNearestValidPoint(const Point& point, const std::vector<Vector3>& obstaclePositions, float obstacleSize);

#endif // THETASTAR_HPP
