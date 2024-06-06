#include <SFML/Graphics.hpp>
#include <iostream>
#include <utility>

class Car 
{
private:
	std::pair <float, float> _cords;
	float _width = 50;
	float _height = 25;
	float _speed = 0;
	float _car_deggre = 0;
	float _wheel_deggre = 0;
public:
	sf::RectangleShape shape;
	float get_width(){return _width;};
	float get_height(){return _height;};
	Car(std::pair<float, float> cords, float car_deggre, float wheel_deggree) : _cords(cords),
																				_speed(0),
																				_car_deggre(car_deggre),
																				_wheel_deggre(wheel_deggree)
	{
		this->shape = sf::RectangleShape(sf::Vector2f(this->_height, this->_width)); 
	};
};

int main()
{
	Car car({100,200}, 90, 90);
	car.shape.setPosition(100,100);
	car.shape.setRotation(45.f);
	car.shape.setOrigin({car.get_height() / 2.0, car.get_width() / 2.0});
	sf::RectangleShape test(sf::Vector2f(5, 5));
	test.setFillColor(sf::Color::Red);
	test.setPosition(100,100);
	// car.shape.setPosition({car.get_height() / 2.0, car.get_width() / 2.0});
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
	sf::Event event;
	while (window.isOpen())
	{
		window.clear(sf::Color::Black);
		while (window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
		}
		window.draw(car.shape);  
		window.draw(test);
		window.display();
		window.clear();
	}
}
