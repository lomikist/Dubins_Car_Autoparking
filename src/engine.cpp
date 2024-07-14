#include "engine.hpp"
#include "helpers.hpp"

#include <iostream>

Engine::Engine()
{
    _window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
        APP_NAME, sf::Style::Titlebar | sf::Style::Close);
    if (!_window.isOpen())
        throw std::runtime_error("-- Failed to crate SFML window.");
    _window.setPosition(sf::Vector2i(0, 0));
}

Engine::~Engine()
{}

Engine& Engine::getInstance()
{
    static Engine engine;
    return engine;
}

void Engine::draw()
{
    _window.clear(sf::Color::Black);
	drawObjects(_car);
    _window.display();
}

template<typename... T>
void Engine::drawObjects(T&&... objects)
{
    (_window.draw(std::forward<T>(objects)), ...);
}

void Engine::handleEvent(const sf::Event& event)
{
    switch (event.type)
    {
    case sf::Event::KeyPressed:
        handleKeyPressedEvent(event.key.code);
        break;
    case sf::Event::Closed:
        _window.close();
        break;
    default:
        break;
    }
}

void Engine::handleKeyPressedEvent(sf::Keyboard::Key key)
{
    switch (key)
    {
    case sf::Keyboard::Escape:
        _window.close();
        break;
    default:
        break;
    }
}

float Engine::measureElapsedTime()
{
    _elapsedTime = _clock.restart().asSeconds();
    return _elapsedTime;
}

sf::RenderWindow& Engine::getWindow()
{
    return _window;
}