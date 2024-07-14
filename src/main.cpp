#include <iostream>
#include <utility>
#include <cmath>
#include <chrono>
#include <thread>

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








// float d2r(float degrees) {
//     return degrees * PI / 180.0;
// }



// 	int _move_direct = 1;//1 - first circle, 2 - forward, 3 - sec circle

// 	float _car_deggre = 0;
// 	float _current_speed = 100;
// 	float _radius = 70;
// 	float _angular_speed = 20;
// 	std::pair<float, float> _dest_tangent_point;

// 	void move_forward(float delta_time)
// 	{
// 		_car_cords.first += _current_speed * delta_time * std::sin(d2r(_car_deggre));
// 		_car_cords.second -= _current_speed * delta_time * std::cos(d2r(_car_deggre));
// 	}

// 	void move_circle(float delta_time) // maybe we can make it depended on radius.
// 	{
// 		float omega = delta_time * (_current_speed / _radius) * (180.0 / PI);
// 		_car_deggre += omega;
// 		if (_car_deggre >= 360)
// 			_car_deggre = 0;		 

// 		_car_cords.first += _current_speed * delta_time * std::sin(d2r(_car_deggre));
// 		_car_cords.second -= _current_speed * delta_time * std::cos(d2r(_car_deggre));
// 	}

// 	float calc_disired_angle(const std::pair<float, float>& point1, const std::pair<float, float>& point2)
// 	{
// 		float deltaX = point2.first - point1.first;
// 		float deltaY = point2.second - point1.second;
// 		double angleRadians = atan2(deltaY, deltaX);
// 		double angleDegrees = angleRadians * 180 / M_PI;
// 		return 90 + angleDegrees;
// 	}
	
// 	void move(float delta_time)
// 	{
// 		check_direction();

// 		if (_move_direct == 2)
// 			move_forward(delta_time);
// 		else if(_move_direct == 1 || _move_direct == 3)
// 			move_circle(delta_time);
// 		shape.setRotation(_car_deggre);
// 		shape.setPosition(_car_cords.first, _car_cords.second);
		
// 	}

// 	Car(std::pair<float, float> cords, float car_deggre, float wheel_deggree) : _car_cords(cords),
// 																				_car_deggre(car_deggre)
// 	{
// 		// _car_start_cords = cords;

// 		shape = sf::RectangleShape(sf::Vector2f(this->_height, this->_width));
// 		shape.setOrigin({_height / 2.f, _width / 2.f});

// 		parking_shape = sf::RectangleShape(sf::Vector2f(this->_height, this->_width));
// 		parking_shape.setOrigin({_height / 2.f, _width / 2.f});
// 		parking_shape.setRotation(_dest_deggre);
// 		parking_shape.setPosition(_dest_cords.first, _dest_cords.second);
// 		calc_centers();
// 	};

// 	/*
// 	* calc dest and car center.
// 	*/
// 	void calc_centers()
// 	{
// 		car_center = get_circle_cord(_car_cords, _car_deggre);
// 		dest_center = get_circle_cord(_dest_cords, _dest_deggre);

// 		_dest_tangent_point.first = dest_center.first - (car_center.first - _car_cords.first); 
// 		_dest_tangent_point.second = dest_center.second - (car_center.second - _car_cords.second);
// 	}

// 	void check_direction()
// 	{
// 		float line_degree = calc_disired_angle(car_center, dest_center); 	

// 		if (_car_deggre < line_degree && _move_direct != 3)
// 			_move_direct = 1;
// 		else if(_move_direct != 3)
// 			_move_direct = 2;
// 		if (std::pow(_car_cords.first - dest_center.first, 2) + std::pow(_car_cords.second - dest_center.second, 2) < std::pow(_radius + 1, 2))
// 			_move_direct = 3;
// 		if (_move_direct == 3 && _car_deggre < _dest_deggre + 1 && _car_deggre > _dest_deggre - 1)
// 			_current_speed = 0;
// 	}

// 	std::pair<float, float> get_circle_cord(const std::pair<float, float>& cords, float angle)
// 	{
// 		std::pair<float, float> circle_cord;// {x, y}

// 		circle_cord.first = cords.first + _radius * std::cos(d2r(angle));
// 		circle_cord.second = cords.second + _radius * std::sin(d2r(angle));

// 		return circle_cord;
// 	}
// };
