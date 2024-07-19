#ifndef PARKING_SPOT_HPP
#define PARKING_SPOT_HPP

#include <SFML/Graphics.hpp>

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

private:
    sf::CircleShape _circle;
    sf::RectangleShape _rect;
};

#endif  /* PARKING_SPOT_HPP */