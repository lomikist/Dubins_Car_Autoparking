#include <cmath>
#include "car.hpp"
#include "helpers.hpp"

Car::Car()
{
    sf::Vector2f size(CAR_WIDTH, CAR_HEIGHT);
    _rect.setSize(size);
    _rect.setOrigin(size / 2.0f);
    _rect.setPosition(CAR_POS_X, CAR_POS_Y);
    _rect.setFillColor(sf::Color(CAR_RED, CAR_GREEN, CAR_BLUE));
    _rect.setRotation(CAR_ROTATION);
    _speed = CAR_SPEED;
    _moveType = CarMoveType::Circle;
    _circle.setRadius(RADIUS);
    _circle.setOrigin(RADIUS, RADIUS);

    // ******************* Testing ************************ //
    _circle.setOutlineColor(sf::Color(CAR_RED, CAR_GREEN, CAR_BLUE));
    _circle.setFillColor(sf::Color::Black);
    _circle.setOutlineThickness(5);
    calcCircleCenterCoords();
}

Car::~Car()
{}

void Car::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_rect, states);
    target.draw(_circle, states);
}

void Car::processMove(float elapsedTime)
{
    if (_moveType == CarMoveType::Forward)
        moveForward(elapsedTime);
    else
        moveCircle(elapsedTime);
}

void Car::moveForward(float elapsedTime)
{
    float rotation = _rect.getRotation();
    float offsetX = elapsedTime * _speed * std::cos(degreeToRadian(rotation));
    float offsetY = elapsedTime * _speed * std::sin(degreeToRadian(rotation));
    _rect.move(offsetX, offsetY);
}

void Car::moveCircle(float elapsedTime)
{
    _angVelocity = radianToDegree(elapsedTime * (_speed / _circle.getRadius()));
    _rect.rotate(_angVelocity);
    moveForward(elapsedTime);
}

void Car::calcCircleCenterCoords()
{
    float rotation = _rect.getRotation();
    const sf::Vector2f& rectPos = _rect.getPosition();
    float x = rectPos.x + _circle.getRadius() * std::sin(degreeToRadian(rotation));
    float y = rectPos.y + _circle.getRadius() * std::cos(degreeToRadian(rotation));
    _circle.setPosition(x, y);
}

float Car::radianToDegree(float radian)
{
    return radian * (180.0f / pi);
}

float Car::degreeToRadian(float degree)
{
    return degree * (pi / 180.0f);
}