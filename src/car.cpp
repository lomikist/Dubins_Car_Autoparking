#include <cmath>
#include "car.hpp"
#include "helpers.hpp"

// TODO: Delete this include after testing
#include <iostream>

Car::Car()
{
    _speed = CAR_SPEED;
    _isAutoParkingOn = AUTO_PARKING;
    sf::Vector2f size(CAR_WIDTH, CAR_HEIGHT);
    _rect.setSize(size);
    _rect.setOrigin(size / 2.0f);
    _rect.setPosition(CAR_POS_X, CAR_POS_Y);
    _rect.setRotation(CAR_ROTATION);
    _circle.setRadius(RADIUS);
    _circle.setOrigin(RADIUS, RADIUS);

    // Colors
    _rect.setFillColor(sf::Color(CAR_RED, CAR_GREEN, CAR_BLUE));
    _circle.setFillColor(sf::Color::Black);
    _circle.setOutlineColor(sf::Color(30, 144, 255));
    _circle.setOutlineThickness(2);
}

Car::~Car()
{}

void Car::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_rect, states);
    target.draw(_circle, states);
}

void Car::processAutoParking(float elapsedTime, ParkingSpot& parkingSpot)
{
    _shortestPath = findShortestPath(parkingSpot);

    // ************** Testing ************** //
    for (auto elem : _paths)
    {
        std::cout << elem.pathLength << ", Path type: " << (int)elem.pathType << std::endl;
    }
    std::cout << "\n\n-- Shortest path\n";
        std::cout << _shortestPath.pathLength << ", Path type: "
            << (int)_shortestPath.pathType << std::endl;
    _isAutoParkingOn = false;
}

void Car::processUserControl(float elapsedTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            move(elapsedTime, Car::MoveType::Left);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            move(elapsedTime, Car::MoveType::Right);
        else
            move(elapsedTime, Car::MoveType::Straight);
    }
}

Car::ParkingPath& Car::findShortestPath(ParkingSpot& parkingSpot)
{
    // Calculate car and parking spot left and right circles centers
    float radius = _circle.getRadius();
    sf::RectangleShape& spotRect = parkingSpot.getRect();
    sf::Vector2f carLeftCirclePos = getCircleCenterPos(_rect, radius, Car::MoveType::Left);
    sf::Vector2f carRightCirclePos = getCircleCenterPos(_rect, radius, Car::MoveType::Right);
    sf::Vector2f spotLeftCirclePos = getCircleCenterPos(spotRect, radius, Car::MoveType::Left);
    sf::Vector2f spotRightCirclePos = getCircleCenterPos(spotRect, radius, Car::MoveType::Right);

    float carRot = _rect.getRotation();
    float spotRot = spotRect.getRotation();
    // Left turn, Straight, Left turn
    addPathToVector(carLeftCirclePos, carRot, spotLeftCirclePos, spotRot, radius, Car::PathType::LSL);
    // Left turn, Straight, Right turn
    addPathToVector(carLeftCirclePos, carRot, spotRightCirclePos, spotRot, radius, Car::PathType::LSR);
    // Right turn, Straight, Left turn
    addPathToVector(carRightCirclePos, carRot, spotLeftCirclePos, spotRot, radius, Car::PathType::RSL);
    // Right turn, Straight, Right turn
    addPathToVector(carRightCirclePos, carRot, spotRightCirclePos, spotRot, radius, Car::PathType::RSR);

    // Return shortest path
    auto cmp = [](const ParkingPath& a, const ParkingPath& b)
    {
        return a.pathLength < b.pathLength;
    };
    auto shortestPathIt = std::min_element(_paths.begin(), _paths.end(), cmp);
    if (shortestPathIt != _paths.end())
        return *shortestPathIt;
    return _paths.back();
}

void Car::addPathToVector(sf::Vector2f& carCirclePos, float carRotation,
    sf::Vector2f& spotCirclePos, float spotRotation, float radius, PathType pathType)
{
    auto [x1, y1] = carCirclePos;
    auto [x2, y2] = spotCirclePos;
    float alphaDegree = radianToDegree(std::atan2(y2 - y1, x2 - x1)) - carRotation;
    float betaDegree = spotRotation - radianToDegree(std::atan2(y2 - y1, x2 - x1) - pi);

    ParkingPath path;
    path.pathType = pathType;
    path.carCirclePos = carCirclePos;
    path.spotCirclePos = spotCirclePos;
    path.carCirclePathLen = radius * degreeMod(alphaDegree, 360.0f);
    path.spotCirclePathLen = radius * degreeMod(betaDegree, 360.0f);
    path.certersDistance = calcDistance(x1, y1, x2, y2);
    path.straightPathLen = path.certersDistance;
    path.pathLength = path.carCirclePathLen + path.straightPathLen + path.spotCirclePathLen;
    _paths.push_back(path);
}

void Car::move(float elapsedTime, MoveType moveType)
{
    if (moveType == MoveType::Straight)
        moveStraight(elapsedTime);
    else
        moveCircle(elapsedTime, moveType);
}

void Car::moveStraight(float elapsedTime)
{
    float angleRadian = degreeToRadian(_rect.getRotation());
    float offsetX = elapsedTime * _speed * std::cos(angleRadian);
    float offsetY = elapsedTime * _speed * std::sin(angleRadian);
    _rect.move(offsetX, offsetY);
}

void Car::moveCircle(float elapsedTime, MoveType moveType)
{
    _angVelocity = radianToDegree(elapsedTime * (_speed / _circle.getRadius()));
    if (moveType == MoveType::Left)
        _rect.rotate(-_angVelocity);
    else
        _rect.rotate(_angVelocity);
    moveStraight(elapsedTime);
}

bool Car::isAutoParkingOn() const
{
    return _isAutoParkingOn;
}
