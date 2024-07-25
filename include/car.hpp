#ifndef CAR_HPP
#define CAR_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "parking_spot.hpp"
#include "path_manager.hpp"

class Car : public sf::Drawable
{
public:
    enum class MoveType
    {
        Left,
        Right,
        Straight
    };

    typedef PathManager::ParkingPath Path;

public:
    Car();
    ~Car();

    Car(const Car&) = delete;
    Car(Car&&) = delete;
    Car& operator=(const Car&) = delete;
    Car& operator=(Car&&) = delete;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void processAutoParking(float elapsedTime, ParkingSpot& parkingSpot);
    void processUserControl(float elapsedTime);

    // Process car move
    void move(float elapsedTime, MoveType moveType);
    void moveStraight(float elapsedTime);
    void moveCircle(float elapsedTime, MoveType moveType);

    bool isAutoParkingOn() const;

private:
    float _speed;
    float _angVelocity;
    bool _isAutoParkingOn;
    sf::CircleShape _circle;
    sf::RectangleShape _rect;
    PathManager _pathManager;
    int state = 0;

    bool isStop = false;

    sf::CircleShape carCirclePoint;
    sf::CircleShape spotCirclePoint;
};

#endif  /* CAR_HPP */