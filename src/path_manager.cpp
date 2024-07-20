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
    addPathToVector(carLeftCirclePos, carRot, spotLeftCirclePos, spotRot, radius, PathType::LSL);
    // Left turn, Straight, Right turn
    addPathToVector(carLeftCirclePos, carRot, spotRightCirclePos, spotRot, radius, PathType::LSR);
    // Right turn, Straight, Left turn
    addPathToVector(carRightCirclePos, carRot, spotLeftCirclePos, spotRot, radius, PathType::RSL);
    // Right turn, Straight, Right turn
    addPathToVector(carRightCirclePos, carRot, spotRightCirclePos, spotRot, radius, PathType::RSR);

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
        std::cout << elem.pathLength << ", Path type: " << (int)elem.pathType <<
        ", distance: " << elem.certersDistance <<
        ", carCircleLen: " << elem.carCirclePathLen <<
        ", spotCircleLen: " << elem.spotCirclePathLen << std::endl;
    }
    std::cout << "\n\n-- Shortest path\n";
        std::cout << _shortestPath.pathLength << ", Path type: "
            << (int)_shortestPath.pathType << std::endl;

    return _shortestPath;
}

void PathManager::addPathToVector(sf::Vector2f& carCirclePos, float carRot,
    sf::Vector2f& spotCirclePos, float spotRot, float radius, PathType pathType)
{
    auto [x1, y1] = carCirclePos;
    auto [x2, y2] = spotCirclePos;
    float alphaRadian = std::atan2(y2 - y1, x2 - x1) - degreeToRadian(carRot);
    float betaRadian = degreeToRadian(spotRot) - (std::atan2(y2 - y1, x2 - x1) - pi);

    // Creating path
    ParkingPath path;
    path.radius = radius;
    path.pathType = pathType;
    path.carCirclePos = carCirclePos;
    path.spotCirclePos = spotCirclePos;
    path.carCirclePathLen = radius * degreeMod(alphaRadian, 2 * pi);
    path.spotCirclePathLen = radius * degreeMod(betaRadian, 2 * pi);
    path.certersDistance = calcDistance(x1, y1, x2, y2);
    path.straightPathLen = path.certersDistance;
    path.pathLength = path.carCirclePathLen + path.straightPathLen + path.spotCirclePathLen;
    _paths.push_back(path);
}


// void Car::ParkingPath::calcTangentPoints()
// {
//     auto [x1, y1] = carCirclePos;
//     auto [x2, y2] = spotCirclePos;
//     float thetaDegree = radianToDegree(atan2f(y2 - y1, x2 - x1));
//     float gammaDegree = radianToDegree(acosf(2 * radius / certersDistance));
//     float alphaDegree = thetaDegree + gammaDegree;
//     float betaDegree = thetaDegree + pi - gammaDegree;

//     carTangentPoint.x = x1 + radius * radianToDegree(cos(alphaDegree));
//     carTangentPoint.y = y1 + radius * radianToDegree(sin(alphaDegree));
//     spotTangentPoint.x = x2 + radius * radianToDegree(cos(betaDegree));
//     spotTangentPoint.y = y2 + radius * radianToDegree(sin(betaDegree));
// }