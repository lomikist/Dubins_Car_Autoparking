#include <cmath>
#include "car.hpp"
#include "helpers.hpp"

Car::Car()
{
    _speed = CAR_SPEED;
    _isAutoParkingOn = AUTO_PARKING;
    sf::Vector2f size(CAR_WIDTH, CAR_HEIGHT);
    _rect.setSize(size);
    _rect.setOrigin(size / 2.0f);
    _rect.setPosition(CAR_POS_X, CAR_POS_Y);
    _rect.setFillColor(sf::Color(CAR_RED, CAR_GREEN, CAR_BLUE));
    _rect.setRotation(CAR_ROTATION);
    _circle.setRadius(RADIUS);
    _circle.setOrigin(RADIUS, RADIUS);

    // ******************* Testing ************************ //
    _circle.setOutlineColor(sf::Color(CAR_RED, CAR_GREEN, CAR_BLUE));
    _circle.setFillColor(sf::Color::Black);
    _circle.setOutlineThickness(2);
    calcCircleCenterCoords();
}

Car::~Car()
{}

void Car::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_rect, states);
    target.draw(_circle, states);
}

void Car::processAutoParking(float elapsedTime)
{
    move(elapsedTime, MoveType::Right);
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

void Car::calcCircleCenterCoords()
{
    const sf::Vector2f& rectPos = _rect.getPosition();
    float angleRadian = degreeToRadian(_rect.getRotation());
    float x = rectPos.x + _circle.getRadius() * std::sin(angleRadian);
    float y = rectPos.y + _circle.getRadius() * std::cos(angleRadian);
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

