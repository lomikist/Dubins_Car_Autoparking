#ifndef CAR_HPP
#define CAR_HPP

#include <SFML/Graphics.hpp>

class Car : public sf::Drawable
{
public:
    Car();
    ~Car();

    Car(const Car&) = delete;
    Car(Car&&) = delete;
    Car& operator=(const Car&) = delete;
    Car& operator=(Car&&) = delete;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    // Process car move
    void processMove(float elapsedTime);
    void moveForward(float elapsedTime);
    void moveCircle(float elapsedTime);

    const sf::CircleShape& getCircle();

private:
    enum class CarMoveType
    {
        Forward,
        Circle,
    };

    void calcCircleCenterCoords();
    float radianToDegree(float radian);
    float degreeToRadian(float degree);

private:
    float _speed;
    float _angVelocity;
    CarMoveType _moveType;
    sf::CircleShape _circle;
    sf::RectangleShape _rect;
};

#endif  /* CAR_HPP */