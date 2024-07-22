#include <cmath>
#include "car.hpp"
#include "helpers.hpp"
#include "path_manager.hpp"

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
    target.draw(_circle, states);
    target.draw(_rect, states);

    // **************** Testing *************** //
    target.draw(carCirclePoint);
    target.draw(spotCirclePoint);
}

void Car::processAutoParking(float elapsedTime, ParkingSpot& parkingSpot)
{
    Path& shortestPath = _pathManager.findShortestPath(_rect,
        parkingSpot.getRect(), _circle.getRadius());
    _circle.setPosition(shortestPath.carCirclePos);
    parkingSpot.getCircle().setPosition(shortestPath.spotCirclePos);






    _isAutoParkingOn = false;
    // **************** Testing *************** //
    carCirclePoint.setPosition(shortestPath.carTangentPoint);
    spotCirclePoint.setPosition(shortestPath.spotTangentPoint);
    carCirclePoint.setFillColor(sf::Color::Green);
    spotCirclePoint.setFillColor(sf::Color::Green);
    carCirclePoint.setRadius(3);
    spotCirclePoint.setRadius(3);
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
