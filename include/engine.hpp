#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SFML/Graphics.hpp>

class Engine final
{
public:
    static Engine& getInstance();
    ~Engine();

    void draw();
    template<typename... T>
    void drawObjects(T&&... objects);

    void handleEvent(const sf::Event& event);

    double measureElapsedTime();

    sf::RenderWindow& getWindow();

private:
    Engine();
    Engine(const Engine&) = delete;
    Engine(Engine&&) = delete;
    Engine& operator=(const Engine&) = delete;
    Engine& operator=(Engine&&) = delete;

private:
	sf::Clock _clock;
    double _elapsedTime;
    sf::RenderWindow _window;
};

#endif  /* ENGINE_HPP */