#include <iostream>
#include "engine.hpp"

int main() try
{
    Engine& engine = Engine::getInstance();
    sf::RenderWindow& window = engine.getWindow();
    sf::Event event;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
            engine.handleEvent(event);

        engine.processFrame();
		engine.draw();
    }
    return 0;
}
catch(const std::exception& e)
{
    std::cerr << "-- " << e.what() << std::endl;
    std::cerr << "-- Terminating the program..." << std::endl;
}
catch(...)
{
    std::cerr << "-- Unknown exception was caught." << std::endl;
    std::cerr << "-- Terminating the program..." << std::endl;
}
