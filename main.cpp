#include <SFML/Graphics.hpp>
#include <iostream>
#include <utility>
#include <cmath>
#include <chrono>
#include <thread>

const double PI = 3.14159265358979323846;

double d2r(double degrees) {
    return degrees * PI / 180.0;
}

double getTime() {
    using namespace std::chrono;
    return duration_cast<duration<double>>(high_resolution_clock::now().time_since_epoch()).count();
}

class Car 
{
private:
	std::pair <float, float> _cords;
	float _width = 50;
	float _height = 25;
	float _car_deggre = 0;
	float _wheel_deggre = 0;
	float _current_speed = 0;
	float _max_speed = 140;
	float _back_max_speed = -80;
public:
	sf::RectangleShape shape;

	const std::pair<float, float>& get_cord(){return _cords;};
	float get_width(){return _width;};
	float get_height(){return _height;};

	void calc_speed_deggre(const sf::Event& event){
        bool A = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        bool S = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
        bool D = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
        bool W = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
        if (A && W)
		{
			_car_deggre--;
			if (_current_speed < _max_speed)
				_current_speed++;
		}
		else if (W && D) 
		{
			_car_deggre++;
			if (_current_speed < _max_speed)
				_current_speed++;
		}
		else if (A && S && _current_speed > 25)
		{
			_car_deggre--;	// cuz move is backward 
			if (_current_speed > _back_max_speed)
				_current_speed--;
		}
		else if (A && S && _current_speed < -25)
		{
			_car_deggre++;	// cuz move is backward 
			if (_current_speed > _back_max_speed)
				_current_speed--;
		}
		else if (S && D && _current_speed > 25) // cuz move is backward 
		{
			_car_deggre++;
			if (_current_speed > _back_max_speed)
				_current_speed--;
		}
		else if (S && D && _current_speed < -25) // cuz move is backward 
		{
			_car_deggre--;
			if (_current_speed > _back_max_speed)
				_current_speed--;
		}
		else if (A && _current_speed > 25) 
			_car_deggre--;
		else if (A && _current_speed < -25) 
			_car_deggre++;
		else if (S && _current_speed > _back_max_speed) 
			_current_speed-=3;
		else if (D && _current_speed > 25) 
			_car_deggre++;
		else if (D && _current_speed < -25) 
			_car_deggre--;
		else if (W && _current_speed < _max_speed) 
			_current_speed++;
	};

	float get_current_deggre(){
		return _car_deggre;
	};
	
	void move(double elapsed_time)
	{
		_cords.first += _current_speed * elapsed_time * std::sin(d2r(_car_deggre));
		_cords.second -= _current_speed * elapsed_time * std::cos(d2r(_car_deggre));
		// std::cout << _car_deggre << std::endl;
		// std::cout << _current_speed << "----" << _back_max_speed << std::endl;
	}

	Car(std::pair<float, float> cords, float car_deggre, float wheel_deggree) : _cords(cords),
																				_current_speed(0),
																				_car_deggre(car_deggre),
																				_wheel_deggre(wheel_deggree)
	{
		this->shape = sf::RectangleShape(sf::Vector2f(this->_height, this->_width)); 
	};

	void decress_speed(sf::RenderWindow &window, const sf::Event& event)
	{
		if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::S)
		{
			double last_time = getTime();
			while (_current_speed > 0)
			{
				double current_time = getTime();
				double elapsed_time = current_time - last_time;
				shape.setRotation(get_current_deggre());
				shape.setPosition(get_cord().first, get_cord().second);


				last_time = current_time;
				window.clear(sf::Color::Black);
				_current_speed--;
				move(elapsed_time);
				window.draw(shape);  
				window.display();
				window.clear();
			}
		}
	}
};

int main()
{
	Car car({100,200}, 0, 0);
	car.shape.setOrigin({car.get_height() / 2.f, car.get_width() / 2.f});

	sf::RenderWindow window(sf::VideoMode(800,800), "SFML window");
	sf::Event event;

	double last_time = getTime();

	while (window.isOpen())
	{
		double current_time = getTime();
        double elapsed_time = current_time - last_time;
        last_time = current_time;

		car.shape.setRotation(car.get_current_deggre());
		car.shape.setPosition(car.get_cord().first, car.get_cord().second);
		window.clear(sf::Color::Black);
		while (window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
				car.calc_speed_deggre(event);
			if (event.type == sf::Event::KeyReleased)
				car.decress_speed(window, event);
		}
		car.move(elapsed_time);
		window.draw(car.shape);  
		window.display();
		window.clear();
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}
}
