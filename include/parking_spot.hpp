#ifndef PARKING_SPOT_HPP
#define PARKING_SPOT_HPP

#include <SFML/Graphics.hpp>
#include "helpers.hpp"

class ParkingSpot : public sf::Drawable
{
public:
    ParkingSpot();
    ~ParkingSpot();

    ParkingSpot(const ParkingSpot&) = delete;
    ParkingSpot(ParkingSpot&&) = delete;
    ParkingSpot& operator=(const ParkingSpot&) = delete;
    ParkingSpot& operator=(ParkingSpot&&) = delete;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    Rect& getRect();
    Circle& getCircle();

private:
    Rect _rect;
    Circle _circle;
};

#endif  /* PARKING_SPOT_HPP */