#include <SFML/Graphics.hpp>
#include <iostream>
#include <utility>
#include <cmath>
#include <chrono>
#include <thread>

const float PI = 3.14159265358979323846;

float d2r(float degrees) {
    return degrees * PI / 180.0;
}

class Engine
{
public:
	sf::Event event;
	sf::Clock clock;
	sf::RenderWindow window;

	float _delta_time = 0;
	sf::Time elapsed_time;
	
	Engine(int width ,int height){
		window.create(sf::VideoMode(width, height), "TESLA autoparking.");
		window.setPosition(sf::Vector2{0,0});
	};
	~Engine() = default;

	template<typename... T>
    void draw(T&... objects) {
        (window.draw(objects), ...);
    }

	float delta_time()
	{
		elapsed_time = clock.restart();
        _delta_time = elapsed_time.asSeconds();
	}
};

class Car 
{
public:
	std::pair <float, float> _car_cords; //{x,y}
	std::pair <float, float> _car_start_cords; //{x,y}


	std::pair <float, float> _dest_cords = {600, 600};//{x,y}
	
	float _dest_deggre = 45;

	float _width = 50;
	float _height = 25;
	
	float _car_deggre = 0;
	float _current_speed = 39;
	float _radius = 70;
	float _angular_speed = 20;

public:

	std::pair<float, float> car_center;
	std::pair<float, float> dest_center;
	std::pair<float, float> dest_tangent_point;

	sf::RectangleShape shape;
	sf::RectangleShape parking_shape;

	const std::pair<float, float>& get_cord(){return _car_cords;};
	float get_width(){return _width;};
	float get_height(){return _height;};


	void move_forward(float delta_time)
	{
		shape.setRotation(_car_deggre);
		shape.setPosition(_car_cords.first, _car_cords.second);
		_car_cords.first += _current_speed * delta_time * std::sin(d2r(_car_deggre));
		_car_cords.second -= _current_speed * delta_time * std::cos(d2r(_car_deggre));
	}

	void move_circle(float delta_time) // maybe we can make it depended on radius.
	{
		float omega = delta_time * (_current_speed / _radius) * (180.0 / PI);
		_car_deggre += omega;
		if (_car_deggre >= 360)
			_car_deggre = 0;		 
		shape.setRotation(_car_deggre);
		shape.setPosition(_car_cords.first, _car_cords.second);
		_car_cords.first += _current_speed * delta_time * std::sin(d2r(_car_deggre));
		_car_cords.second -= _current_speed * delta_time * std::cos(d2r(_car_deggre));
	}

	float calc_disired_angle(const std::pair<float, float>& point1, const std::pair<float, float>& point2)
	{
		float deltaX = point2.first - point1.first;
		float deltaY = point2.second - point1.second;

		double angleRadians = atan2(deltaY, deltaX);

		double angleDegrees = angleRadians * 180 / M_PI;
		return 90 + angleDegrees;
	}
	
	void move(float delta_time)
	{
		float line_degree = calc_disired_angle(car_center, dest_center); 	
		//TODO calc_disired in not workinkg well check this ,
		//TODO car rotation cordinates are slightly not correct check this. and 
		std::cout << _car_deggre << "==" << line_degree << std::endl;
		if (_car_deggre < line_degree)
			move_circle(delta_time);
		else
			move_forward(delta_time);
	}

	Car(std::pair<float, float> cords, float car_deggre, float wheel_deggree) : _car_cords(cords),
																				_car_deggre(car_deggre)
	{
		// _car_start_cords = cords;

		shape = sf::RectangleShape(sf::Vector2f(this->_height, this->_width));
		shape.setOrigin({_height / 2.f, _width / 2.f});

		parking_shape = sf::RectangleShape(sf::Vector2f(this->_height, this->_width));
		parking_shape.setOrigin({_height / 2.f, _width / 2.f});
		parking_shape.setRotation(_dest_deggre);
		parking_shape.setPosition(_dest_cords.first, _dest_cords.second);

		/*
		* calc dest and car center.
		*/
		car_center = get_circle_cord(_car_cords, _car_deggre);
		dest_center = get_circle_cord(_dest_cords, _dest_deggre);

		dest_tangent_point.first = dest_center.first - (car_center.first - _car_cords.first); 
		dest_tangent_point.second = dest_center.second - (car_center.second - _car_cords.second);
	};

	std::pair<float, float> get_circle_cord(const std::pair<float, float>& cords, float angle)
	{
		std::pair<float, float> circle_cord;// {x, y}

		circle_cord.first = cords.first + _radius * std::cos(d2r(angle));
		circle_cord.second = cords.second + _radius * std::sin(d2r(angle));

		return circle_cord;
	}
};




int main()
{
	Car car({900,100}, 0, 0);
	Engine eng(1900, 800);

	while (eng.window.isOpen())
	{
		eng.window.clear(sf::Color::Black);
		eng.delta_time();
		while (eng.window.pollEvent(eng.event))
		{
			if (eng.event.type == sf::Event::Closed)
				eng.window.close();
			// if (eng.event.type == sf::Event::KeyPressed){
			// 	car.calc_speed(eng._delta_time);
			// }
		}
		car.move(eng._delta_time);

		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(car.car_center.first, car.car_center.second)),
			sf::Vertex(sf::Vector2f(car.dest_center.first, car.dest_center.second))
		};

		eng.window.draw(line, 2, sf::Lines);

		eng.draw(car.shape, car.parking_shape);  
		eng.window.display();
		eng.window.clear();
	}
}
