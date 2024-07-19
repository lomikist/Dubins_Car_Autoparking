#include <SFML/Graphics.hpp>
#include <cmath>
#include "helpers.hpp"

float radianToDegree(float radian)
{
    return radian * (180.0f / pi);
}

float degreeToRadian(float degree)
{
    return degree * (pi / 180.0f);
}

void setCircleCenterPos(const sf::RectangleShape& rect, sf::CircleShape& circle)
{
    const sf::Vector2f& rectPos = rect.getPosition();
    float angleRadian = degreeToRadian(rect.getRotation());
    float x = rectPos.x + circle.getRadius() * std::sin(angleRadian);
    float y = rectPos.y + circle.getRadius() * std::cos(angleRadian);
    circle.setPosition(x, y);
}