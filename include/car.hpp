#ifndef CAR_HPP
#define CAR_HPP

#include <SFML/Graphics.hpp>

class Car : public sf::RectangleShape
{
public:
    Car();
    ~Car();

    Car(const Car&) = delete;
    Car(Car&&) = delete;
    Car& operator=(const Car&) = delete;
    Car& operator=(Car&&) = delete;

    // Process car move
    void processMove(float elapsedTime);
    void moveCircle(float elapsedTime);

private:
    enum class CarMoveType
    {
        Forward,
        Circle,
    };

private:
    float _speed;
    float _radius;
    CarMoveType _moveType;
};

#endif  /* CAR_HPP */