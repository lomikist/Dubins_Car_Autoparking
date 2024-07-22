#ifndef PATH_MANAGER_HPP
#define PATH_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include "parking_spot.hpp"
#include "helpers.hpp"

class PathManager
{
public:
    struct ParkingPath
    {
        // L = left
        // R = Right
        // S = straight
        enum class Type
        {
            LSL,
            LSR,
            RSL,
            RSR,
        };

        void calcTangentPoints();

        Type type;
        float radius;
        float pathLength;
        float certersDistance;
        float carCirclePathLen;
        float straightPathLen;
        float spotCirclePathLen;
        sf::Vector2f carCirclePos;
        sf::Vector2f spotCirclePos;
        sf::Vector2f carTangentPoint;
        sf::Vector2f spotTangentPoint;
    };

    typedef ParkingPath::Type PathType;

public:
    PathManager() = default;
    ~PathManager() = default;

    PathManager(const PathManager&) = delete;
    PathManager(PathManager&&) = delete;
    PathManager& operator=(const PathManager&) = delete;
    PathManager& operator=(PathManager&&) = delete;

    ParkingPath& findShortestPath(Rect& carRect, Rect& spotRect, float radius);
    void addPathToVector(sf::Vector2f& carCirclePos, float carRot,
        sf::Vector2f& spotCirclePos, float spotRot, float radius, PathType pathType);

private:
    ParkingPath _shortestPath;
    std::vector<ParkingPath> _paths;
};

#endif  /* PATH_MANAGER_HPP */