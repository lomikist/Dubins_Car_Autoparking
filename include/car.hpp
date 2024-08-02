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

    // Process car move
    void processMove(float elapsedTime, ParkingSpot& parkingSpot);
    void processAutoParking(float elapsedTime, ParkingSpot& parkingSpot);
    void processUserControl(float elapsedTime);
    void moveStraight(float elapsedTime);
    void moveCircle(float elapsedTime, MoveType moveType);

    bool isAutoParkingOn() const;

private:
    Rect _rect;
    Circle _circle;
    float _speed;
    float _angVelocity;
    bool _isAutoParkingOn;
    PathManager _pathManager;

    int state = 0;
    bool isStop = false;
    Circle carCirclePoint;
    Circle spotCirclePoint;
};

#endif  /* CAR_HPP */