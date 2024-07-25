#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SFML/Graphics.hpp>
#include "car.hpp"
#include "parking_spot.hpp"

// Singleton design pattern is used
class Engine final
{
public:
    static Engine& getInstance();
    ~Engine();

    void processFrame();
    float measureElapsedTime();

    void draw();
    template<typename... T>
    void drawObjects(T&&... objects);

    // Event handlers
    void handleEvent(const sf::Event& event);
    void handleKeyPressedEvent(sf::Keyboard::Key key);

    sf::RenderWindow& getWindow();

private:
    Engine();
    Engine(const Engine&) = delete;
    Engine(Engine&&) = delete;
    Engine& operator=(const Engine&) = delete;
    Engine& operator=(Engine&&) = delete;

private:
    Car _car;
	sf::Clock _clock;
    float _elapsedTime;
    ParkingSpot _parkingSpot;
    sf::RenderWindow _window;
};

#endif  /* ENGINE_HPP */