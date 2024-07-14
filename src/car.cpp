#include "car.hpp"
#include "helpers.hpp"

Car::Car()
{
    sf::Vector2f size(CAR_WIDTH, CAR_HEIGHT);
    setSize(size);
    setPosition(100, 100);
    setFillColor(sf::Color(100, 150, 25));
    setOrigin(size / 2.f);
}

Car::~Car()
{}