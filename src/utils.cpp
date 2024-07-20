#include <cmath>
#include "helpers.hpp"
#include "car.hpp"

float radianToDegree(float radian)
{
    return radian * (180.0f / pi);
}

float degreeToRadian(float degree)
{
    return degree * (pi / 180.0f);
}

float degreeMod(float degree, float x)
{
    return fmodf(degree + x, x);
}

float calcDistance(float x1, float y1, float x2, float y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

sf::Vector2f getCircleCenterPos(const sf::RectangleShape& rect,
    float radius, Car::MoveType moveType)
{
    const sf::Vector2f& rectPos = rect.getPosition();
    float angleRadian = degreeToRadian(rect.getRotation());
    float offsetX = radius * std::sin(angleRadian);
    float offsetY = radius * std::cos(angleRadian);
    if (moveType == Car::MoveType::Left)
        return {rectPos.x + offsetX, rectPos.y - offsetY};
    else
        return {rectPos.x - offsetX, rectPos.y + offsetY};
}