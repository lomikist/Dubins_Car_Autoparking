#include "car.hpp"
#include "helpers.hpp"

#include <iostream>

Car::Car()
{
    sf::Vector2f size(CAR_WIDTH, CAR_HEIGHT);
    setSize(size);
    setPosition(START_POS_X, START_POS_Y);
    setFillColor(sf::Color(CAR_RED, CAR_GREEN, CAR_BLUE));
    setOrigin(size / 2.f);
    setRotation(CAR_ROTATION);
    _speed = CAR_SPEED;
    _radius = CAR_RADIUS;
    _moveType = CarMoveType::Circle;
}

Car::~Car()
{}

void Car::processMove(float elapsedTime)
{
    // if (_moveType == CarMoveType::Forward)
    //     moveForward(elapsedTime);
    // else
        moveCircle(elapsedTime);

    // float omega = _elapsedTime * (_speed / _radius) * (180.0 / pi);
    // _car.rotate(omega);

    // float x = _speed * _elapsedTime * std::cos(d2r(_car.getRotation()));
    // float y = _speed * _elapsedTime * std::sin(d2r(_car.getRotation()));
    // _car.move(x, y);
}

void Car::moveCircle(float elapsedTime)
{
}