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

float calcDistance(float x1, float y1, float x2, float y2)
{
    return sqrtf(powf(x2 - x1, 2) + powf(y2 - y1, 2));
}

float calcDistance(const sf::Vector2f& point1, const sf::Vector2f& point2)
{
    return sqrtf(powf(point2.x - point1.x, 2) + powf(point2.y - point1.y, 2));
}

sf::Vector2f getCircleCenterPos(const Rect& rect, float radius, int moveType)
{
    const sf::Vector2f& rectPos = rect.getPosition();
    float angleRad = degreeToRadian(rect.getRotation());
    float offsetX = radius * sinf(angleRad);
    float offsetY = radius * cosf(angleRad);

    if (static_cast<Car::MoveType>(moveType) == Car::MoveType::Left)
        return {rectPos.x + offsetX, rectPos.y - offsetY};
    else
        return {rectPos.x - offsetX, rectPos.y + offsetY};
}