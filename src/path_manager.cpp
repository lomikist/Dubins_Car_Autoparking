#include <cmath>
#include "path_manager.hpp"
#include "car.hpp"

// TODO: Delete this include after testing
#include <iostream>

PathManager::ParkingPath& PathManager::findShortestPath(Rect& carRect, Rect& spotRect, float radius)
{
    if (!borsh)
        return _shortestPath;

    // Calculate car and parking spot left and right circles centers
    sf::Vector2f carLeftCirclePos = getCircleCenterPos(carRect, radius, (int)Car::MoveType::Left);
    sf::Vector2f carRightCirclePos = getCircleCenterPos(carRect, radius, (int)Car::MoveType::Right);
    sf::Vector2f spotLeftCirclePos = getCircleCenterPos(spotRect, radius, (int)Car::MoveType::Left);
    sf::Vector2f spotRightCirclePos = getCircleCenterPos(spotRect, radius, (int)Car::MoveType::Right);

    // Left turn, Straight, Left turn
    addPathToVector(carRect, carLeftCirclePos, spotRect, spotLeftCirclePos, radius, PathType::LSL);
    // Left turn, Straight, Right turn
    addPathToVector(carRect, carLeftCirclePos, spotRect, spotRightCirclePos, radius, PathType::LSR);
    // Right turn, Straight, Left turn
    addPathToVector(carRect, carRightCirclePos, spotRect, spotLeftCirclePos, radius, PathType::RSL);
    // Right turn, Straight, Right turn
    addPathToVector(carRect, carRightCirclePos, spotRect, spotRightCirclePos, radius, PathType::RSR);
    if (_paths.empty())
        throw std::runtime_error("Can't find shortest path!");

    // Find shortest path
    auto cmp = [](const ParkingPath& a, const ParkingPath& b)
    {
        return a.pathLength < b.pathLength;
    };
    auto shortestPathIt = std::min_element(_paths.begin(), _paths.end(), cmp);
    if (shortestPathIt != _paths.end())
        _shortestPath = *shortestPathIt;
    else
        _shortestPath = _paths.back();

    // ************** Testing ************** //
    // for (auto elem : _paths)
    // {
    //     std::cout << "Type:  " << (int)elem.type << std::endl
    //     << "D:  " << elem.certersDistance << std::endl
    //     << "Car tangent point x:  " << elem.carTangentPoint.x << std::endl
    //     << "Car tangent point y:  " << elem.carTangentPoint.y << std::endl
    //     << "Spot tangent point x:  " << elem.spotTangentPoint.x << std::endl
    //     << "Spot tangent point y:  " << elem.spotTangentPoint.y << std::endl
    //     << "Car cirlce path len:  " << elem.carCirclePathLen << std::endl
    //     << "Spot cirlce path len:  " << elem.spotCirclePathLen << std::endl
    //     << "Path len:  " << elem.pathLength << std::endl
    //     << std::endl << std::endl << std::endl;
    // }
    // std::cout << "\n\n-- Shortest path\n";
    //     std::cout << _shortestPath.pathLength << ", Path type: "
    //         << (int)_shortestPath.type << std::endl;

    borsh = false;
    return _shortestPath;
}

void PathManager::addPathToVector(Rect& carRect, sf::Vector2f& carCirclePos,
    Rect& spotRect, sf::Vector2f& spotCirclePos, float radius, PathType pathType)
{
    auto [x1, y1] = carRect.getPosition();
    auto [x2, y2] = spotRect.getPosition();
    auto [Cx1, Cy1] = carCirclePos;
    auto [Cx2, Cy2] = spotCirclePos;

    // Creating path
    ParkingPath path;
    path.type = pathType;
    path.radius = radius;
    path.carCirclePos = carCirclePos;
    path.spotCirclePos = spotCirclePos;
    path.certersDistance = calcDistance(Cx1, Cy1, Cx2, Cy2);
    path.calcTangentPoints();

    float d1 = calcDistance(x1, y1, path.carTangentPoint.x, path.carTangentPoint.y);
    float alphaRad = 2 * asinf(d1 / (2 * radius));

    float d2 = calcDistance(x2, y2, path.spotTangentPoint.x, path.spotTangentPoint.y);
    float betaRad = 2 * asinf(d2 / (2 *  radius));

    path.carCirclePathLen = radius * alphaRad;
    path.spotCirclePathLen = radius * betaRad;
    path.straightPathLen = path.certersDistance;
    path.pathLength = path.carCirclePathLen + path.straightPathLen + path.spotCirclePathLen;
    _paths.push_back(path);
}

void PathManager::ParkingPath::calcTangentPoints()
{
    auto [x1, y1] = carCirclePos;
    auto [x2, y2] = spotCirclePos;

    float thetaRad;
    float alphaRad = atan2f(y2 - y1, x2 - x1);
    if (type == PathType::LSL || type == PathType::RSR)
        thetaRad = acosf(radius / certersDistance);
    else
        thetaRad = acosf(2 * radius / certersDistance);

    if (type == PathType::LSL)
    {
        carTangentPoint.x = x1 + radius * cos(alphaRad + thetaRad);
        carTangentPoint.y = y1 + radius * sin(alphaRad + thetaRad);
        spotTangentPoint.x = x2 + radius * cos(alphaRad + thetaRad);
        spotTangentPoint.y = y2 + radius * sin(alphaRad + thetaRad);
    }
    else if (type == PathType::LSR)
    {
        carTangentPoint.x = x1 + radius * cos(alphaRad + thetaRad);
        carTangentPoint.y = y1 + radius * sin(alphaRad + thetaRad);
        spotTangentPoint.x = x2 + radius * cos(alphaRad + thetaRad + pi);
        spotTangentPoint.y = y2 + radius * sin(alphaRad + thetaRad + pi);
    }
    else if (type == PathType::RSL)
    {
        carTangentPoint.x = x1 + radius * cos(alphaRad - thetaRad);
        carTangentPoint.y = y1 + radius * sin(alphaRad - thetaRad);
        spotTangentPoint.x = x2 + radius * cos(alphaRad - thetaRad + pi);
        spotTangentPoint.y = y2 + radius * sin(alphaRad - thetaRad + pi);
    }
    else if (type == PathType::RSR)
    {
        carTangentPoint.x = x1 + radius * cos(alphaRad - thetaRad);
        carTangentPoint.y = y1 + radius * sin(alphaRad - thetaRad);
        spotTangentPoint.x = x2 + radius * cos(alphaRad - thetaRad);
        spotTangentPoint.y = y2 + radius * sin(alphaRad - thetaRad);
    }
}