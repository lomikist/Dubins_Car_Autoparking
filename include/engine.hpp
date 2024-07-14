#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "car.hpp"

// Singleton design pattern is used
class Engine final
{
public:
    static Engine& getInstance();
    ~Engine();

    void draw();

    template<typename... T>
    void drawObjects(T&&... objects);

    // Event handlers
    void handleEvent(const sf::Event& event);
    void handleKeyPressedEvent(sf::Keyboard::Key key);

    float measureElapsedTime();

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
    sf::RenderWindow _window;
};

#endif  /* ENGINE_HPP */