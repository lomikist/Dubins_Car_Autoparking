#include <cmath>
#include "path_manager.hpp"
#include "car.hpp"

// TODO: Delete this include after testing
#include <iostream>

PathManager::ParkingPath& PathManager::findShortestPath(Rect& carRect, Rect& spotRect, float radius)
{
    // Calculate car and parking spot left and right circles centers
    sf::Vector2f carLeftCirclePos = getCircleCenterPos(carRect, radius, (int)Car::MoveType::Left);
    sf::Vector2f carRightCirclePos = getCircleCenterPos(carRect, radius, (int)Car::MoveType::Right);
    sf::Vector2f spotLeftCirclePos = getCircleCenterPos(spotRect, radius, (int)Car::MoveType::Left);
    sf::Vector2f spotRightCirclePos = getCircleCenterPos(spotRect, radius, (int)Car::MoveType::Right);

    float carRot = carRect.getRotation();
    float spotRot = spotRect.getRotation();
    // Left turn, Straight, Left turn
    // addPathToVector(carLeftCirclePos, carRot, spotLeftCirclePos, spotRot, radius, PathType::LSL);
    // Left turn, Straight, Right turn
    // addPathToVector(carLeftCirclePos, carRot, spotRightCirclePos, spotRot, radius, PathType::LSR);
    // Right turn, Straight, Left turn
    addPathToVector(carRightCirclePos, carRot, spotLeftCirclePos, spotRot, radius, PathType::RSL);
    // Right turn, Straight, Right turn
    // addPathToVector(carRightCirclePos, carRot, spotRightCirclePos, spotRot, radius, PathType::RSR);
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
    for (auto elem : _paths)
    {
        std::cout << "Type:  " << (int)elem.type << std::endl
        << "D:  " << elem.certersDistance << std::endl
        << "Car tangent point x:  " << elem.carTangentPoint.x << std::endl
        << "Car tangent point y:  " << elem.carTangentPoint.y << std::endl
        << "Spot tangent point x:  " << elem.spotTangentPoint.x << std::endl
        << "Spot tangent point y:  " << elem.spotTangentPoint.y << std::endl
        << std::endl << std::endl << std::endl;
    }
    // std::cout << "\n\n-- Shortest path\n";
    //     std::cout << _shortestPath.pathLength << ", Path type: "
    //         << (int)_shortestPath.type << std::endl;

    return _shortestPath;
}

void PathManager::addPathToVector(sf::Vector2f& carCirclePos, float carRot,
    sf::Vector2f& spotCirclePos, float spotRot, float radius, PathType pathType)
{
    auto [x1, y1] = carCirclePos;
    auto [x2, y2] = spotCirclePos;

    // float alphaRadian;
    // float betaRadian;


    // Creating path
    ParkingPath path;
    path.type = pathType;
    path.radius = radius;
    path.carCirclePos = carCirclePos;
    path.spotCirclePos = spotCirclePos;
    path.certersDistance = calcDistance(x1, y1, x2, y2);
    path.calcTangentPoints();











    // float alphaRadian = degreeToRadian(calcAngle());
    // float betaRadian = degreeToRadian(calcAngle());

    // path.carCirclePathLen = radius * degreeMod(alphaRadian, 2 * pi);
    // path.spotCirclePathLen = radius * degreeMod(betaRadian, 2 * pi);
    // path.straightPathLen = path.certersDistance;
    // path.pathLength = path.carCirclePathLen + path.straightPathLen + path.spotCirclePathLen;
    _paths.push_back(path);
}

void PathManager::ParkingPath::calcTangentPoints()
{
    auto [x1, y1] = carCirclePos;
    auto [x2, y2] = spotCirclePos;

    float alphaRad;
    // if (x1 < x2)
        alphaRad = fabsf(atan2f(y2 - y1, x2 - x1));
    // else
        // alphaRad = pi - fabsf(atan2f(y2 - y1, x2 - x1));

    // // For outer tangent points
    // if (type == PathType::LSL || type == PathType::RSR)
    // {
    //     float alphaRad = atanf(radius / certersDistance);
    //     carTangentPoint.x = x1 + radius * cos(thetaRad + alphaRad);
    //     carTangentPoint.y = y1 + radius * sin(thetaRad + alphaRad);
    //     spotTangentPoint.x = x2 + radius * cos(thetaRad + alphaRad);
    //     spotTangentPoint.y = y2 + radius * sin(thetaRad + alphaRad);
    // }
    // else // For inner tangent points
    // {
        float betaRad = asinf(2 * radius / certersDistance);
        float gammaRad = alphaRad - betaRad;
        gammaRad = pi/2 - gammaRad;
        carTangentPoint.x = x1 - radius * cos(gammaRad);
        carTangentPoint.y = y1 + radius * sin(gammaRad);
        spotTangentPoint.x = x2 + radius * cos(gammaRad);
        spotTangentPoint.y = y2 - radius * sin(gammaRad);
    // }
}