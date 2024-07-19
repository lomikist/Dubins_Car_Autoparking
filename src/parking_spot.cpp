#include "parking_spot.hpp"
#include "helpers.hpp"

ParkingSpot::ParkingSpot()
{
    sf::Vector2f size(CAR_WIDTH, CAR_HEIGHT);
    _rect.setSize(size);
    _rect.setOrigin(size / 2.0f);
    _rect.setPosition(SPOT_POS_X, SPOT_POS_Y);
    _rect.setRotation(SPOT_ROTATION);
    _circle.setRadius(RADIUS);
    _circle.setOrigin(RADIUS, RADIUS);

    // Colors
    _rect.setFillColor(sf::Color(SPOT_RED, SPOT_GREEN, SPOT_BLUE));
    _circle.setFillColor(sf::Color::Black);
    _circle.setOutlineColor(sf::Color(30, 144, 255));
    _circle.setOutlineThickness(2);
}

ParkingSpot::~ParkingSpot()
{}

void ParkingSpot::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_rect, states);
    target.draw(_circle, states);
}

sf::CircleShape& ParkingSpot::getCircle()
{
    return _circle;
}

sf::RectangleShape& ParkingSpot::getRect()
{
    return _rect;
}