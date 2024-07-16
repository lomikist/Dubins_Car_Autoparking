#include "car.hpp"
#include "helpers.hpp"

#include <cmath>

float d2r(float degrees) {
    return degrees * pi / 180.0;
}

Car::Car()
{
    sf::Vector2f size(CAR_WIDTH, CAR_HEIGHT);
    setSize(size);
    setPosition(START_POS_X, START_POS_Y);
    setFillColor(sf::Color(CAR_RED, CAR_GREEN, CAR_BLUE));
    setOrigin(size / 2.0f);
    setRotation(CAR_ROTATION);
    _speed = CAR_SPEED;
    _radius = CAR_RADIUS;
    _moveType = CarMoveType::Circle;
}

Car::~Car()
{}

void Car::processMove(float elapsedTime)
{
    if (_moveType == CarMoveType::Forward)
        moveForward(elapsedTime);
    else
        moveCircle(elapsedTime);
}

void Car::moveForward(float elapsedTime)
{
    float rotation = getRotation();
    float offsetX = elapsedTime * _speed * std::cos(degreeToRadian(rotation));
    float offsetY = elapsedTime * _speed * std::sin(degreeToRadian(rotation));
    move(offsetX, offsetY);
}

void Car::moveCircle(float elapsedTime)
{
    _angularVelocity = radianToDegree(elapsedTime * (_speed / _radius));
    rotate(_angularVelocity);
    moveForward(elapsedTime);
}

float Car::radianToDegree(float radian)
{
    return radian * (180.0f / pi);
}

float Car::degreeToRadian(float degree)
{
    return degree * (pi / 180.0f);
}