#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <iostream>

int main() {
    // Create a window with SFML
    sf::RenderWindow window(sf::VideoMode(800, 600), "ImGui + SFML Example");
    window.setFramerateLimit(60);

    // Initialize ImGui-SFML
    ImGui::SFML::Init(window);

    // Clock for managing delta time
    sf::Clock deltaClock;

    // Main loop
    while (window.isOpen()) {
        // Event processing
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Update ImGui-SFML
        ImGui::SFML::Update(window, deltaClock.restart());

        // Start ImGui frame
        ImGui::Begin("Hello, world!");
        if (ImGui::Button("Click me")) {
            std::cout << "Button clicked!" << std::endl;
        }
        ImGui::End();

        // Clear window
        window.clear();

        // Render ImGui
        ImGui::SFML::Render(window);

        // Display window
        window.display();
    }

    // Cleanup ImGui-SFML
    ImGui::SFML::Shutdown();

    return 0;
}
