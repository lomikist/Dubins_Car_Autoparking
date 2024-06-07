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
	float _current_speed = 0;
	float _max_speed = 30;
public:
	sf::RectangleShape shape;

	const std::pair<float, float>& get_cord(){return _cords;};
	float get_width(){return _width;};
	float get_height(){return _height;};

	void move(const sf::Event& event){
        bool A = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        bool S = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
        bool D = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
        bool W = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
        if (A && W)
		{
			_car_deggre--;
			_current_speed++;
		}
		else if (A && S)
		{
			_car_deggre--;
			_current_speed--;
		}
		else if (W && D) 
		{
			_car_deggre++;
			_current_speed--;
		}
		else if (S && D) 
		{
			_car_deggre++;
			_current_speed++;
		}
		else if (A)
			_car_deggre--;
		else if (S) 
			_current_speed--;
		else if (D) 
			_car_deggre++;
		else if (W) 
			_current_speed++;
	};

	float get_current_deggre(){
		return _car_deggre;
	};
	
	void calculate_cords()
	{

	}

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
	
	car.shape.setOrigin({car.get_height() / 2.f, car.get_width() / 2.f});
	// sf::RectangleShape test(sf::Vector2f(5, 5));
	// test.setFillColor(sf::Color::Red);
	// test.setPosition(100,100);
	// car.shape.setPosition({car.get_height() / 2.0, car.get_width() / 2.0});
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
	sf::Event event;
	while (window.isOpen())
	{
		car.shape.setRotation(car.get_current_deggre());
		car.shape.setPosition(car.get_cord().first, car.get_cord().second);
		window.clear(sf::Color::Black);
		while (window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
				car.move(event);
		}
		window.draw(car.shape);  
		window.display();
		window.clear();
	}
}
