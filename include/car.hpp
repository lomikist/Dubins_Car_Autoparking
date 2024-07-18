#ifndef CAR_HPP
#define CAR_HPP

#include <SFML/Graphics.hpp>

class Car : public sf::Drawable
{
public:
    enum class MoveType
    {
        Left,
        Right,
        Straight
    };

public:
    Car();
    ~Car();

    Car(const Car&) = delete;
    Car(Car&&) = delete;
    Car& operator=(const Car&) = delete;
    Car& operator=(Car&&) = delete;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void processAutoParking(float elapsedTime);
    void processUserControl(float elapsedTime);

    // Process car move
    void move(float elapsedTime, MoveType moveType);
    void moveStraight(float elapsedTime);
    void moveCircle(float elapsedTime, MoveType moveType);

    bool isAutoParkingOn() const;

private:
    void calcCircleCenterCoords();
    float radianToDegree(float radian);
    float degreeToRadian(float degree);

private:
    float _speed;
    float _angVelocity;
    bool _isAutoParkingOn;
    sf::CircleShape _circle;
    sf::RectangleShape _rect;
};

#endif  /* CAR_HPP */