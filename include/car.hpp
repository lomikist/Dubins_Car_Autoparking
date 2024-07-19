#ifndef CAR_HPP
#define CAR_HPP

#include <vector>
#include "parking_spot.hpp"

class Car : public sf::Drawable
{
public:
    enum class MoveType
    {
        Left,
        Right,
        Straight
    };

    struct ParkingPath
    {
        // L = left
        // R = Right
        // S = straight
        enum class Type
        {
            LSL,
            LSR,
            RSL,
            RSR,
        };

        Type pathType;
        float pathLength;
        float certersDistance;
        float carCirclePathLen;
        float straightPathLen;
        float spotCirclePathLen;
        sf::Vector2f carCirclePos;
        sf::Vector2f spotCirclePos;
    };

    typedef Car::ParkingPath::Type PathType;

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

    ParkingPath& findShortestPath(ParkingSpot& parkingSpot);
    void addPathToVector(sf::Vector2f& carCirclePos, float carRotation,
        sf::Vector2f& spotCirclePos, float spotRotation, float radius, PathType pathType);
    
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
    ParkingPath _shortestPath;
    std::vector<ParkingPath> _paths;
};

#endif  /* CAR_HPP */