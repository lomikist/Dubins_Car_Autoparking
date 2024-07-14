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

private:
};

#endif  /* CAR_HPP */