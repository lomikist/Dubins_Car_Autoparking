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

class Engine
{
public:
	sf::Event event;
	sf::Clock clock;
	sf::RenderWindow window;

	double _delta_time = 0;
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

	double delta_time()
	{
		elapsed_time = clock.restart();
        _delta_time = elapsed_time.asSeconds();
	}
};

class Car 
{
public:
	std::pair <double, double> _cords; //{x,y}
	std::pair <double, double> _dest_cords = {700, 100};//{x,y}
	
	double _dest_deggre = 45;


	double _width = 50;
	double _height = 25;
	
	double _car_deggre = 0;
	double _current_speed = 39;
	double _radius = 100;
	double _angular_speed = 20;

	// double _max_speed = 50;
	// double _back_max_speed = -40;
	// double _wheel_deggre = 0;
	// double _accel = 2;

public:
	sf::RectangleShape shape;
	sf::RectangleShape parking_shape;

	const std::pair<double, double>& get_cord(){return _cords;};
	double get_width(){return _width;};
	double get_height(){return _height;};


	void move_forward(float delta_time)
	{
		shape.setRotation(_car_deggre);
		shape.setPosition(_cords.first, _cords.second);
		_cords.first += _current_speed * delta_time * std::sin(d2r(_car_deggre));
		_cords.second -= _current_speed * delta_time * std::cos(d2r(_car_deggre));
	}

	void move_circle(float delta_time) // maybe we can make it depended on radius.
	{
		double omega = delta_time * (_current_speed / _radius) * (180.0 / PI);
		_car_deggre += omega;
		if (_car_deggre >= 360)
			_car_deggre = 0;		 
		shape.setRotation(_car_deggre);
		shape.setPosition(_cords.first, _cords.second);
		_cords.first += _current_speed * delta_time * std::sin(d2r(_car_deggre));
		_cords.second -= _current_speed * delta_time * std::cos(d2r(_car_deggre));
	}

	double calc_disired_angle(const std::pair<double, double>& first, const std::pair<double, double>& second)
	{
		double deltaX = second.first - first.first;
		double deltaY = second.second + first.second;
		double angleRadians = std::atan2(deltaY, deltaX);
		double angleDegrees = angleRadians * 180.0 / M_PI;
		return angleDegrees;
	}
	
	void move(float delta_time)
	{
		auto car_center = get_circle_cord(_cords, _car_deggre);
		auto dest_center = get_circle_cord(_dest_cords, _dest_deggre);

		double line_degree = calc_disired_angle(car_center, dest_center); 

		//TODO calc_disired in not workinkg well check this ,
		//TODO car rotation cordinates are slightly not correct check this. and 
		if (_car_deggre < line_degree - 2)
			move_circle(delta_time);
		else
			move_forward(delta_time);
	}

	double get_current_deggre(){
		return _car_deggre;
	};

	Car(std::pair<double, double> cords, double car_deggre, double wheel_deggree) : _cords(cords),
																				_car_deggre(car_deggre)
	{
		shape = sf::RectangleShape(sf::Vector2f(this->_height, this->_width));
		shape.setOrigin({_height / 2., _width / 2.});
		
		parking_shape = sf::RectangleShape(sf::Vector2f(this->_height, this->_width));
		parking_shape.setOrigin({_height / 2., _width / 2.});
		parking_shape.setRotation(_dest_deggre);
		parking_shape.setPosition(_dest_cords.first, _dest_cords.second);
	};

	std::pair<double, double> get_circle_cord(const std::pair<double, double>& cords, double angle)
	{
		std::pair<double, double> circle_cord;// {x, y}

		circle_cord.first = cords.first + _radius * std::cos(d2r(angle));
		circle_cord.second = cords.second + _radius * std::sin(d2r(angle));

		return circle_cord;
	}

	void draw_circe(Engine& engine)
	{
		sf::CircleShape circle(_radius);
		circle.setFillColor(sf::Color::Green);
		circle.setPosition(100 , 500 - _radius);
		engine.window.draw(circle);
	}



};




int main()
{
	Car car({100,500}, 0, 0);
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
		// car.calc_speed(eng._delta_time);
		car.move(eng._delta_time);
		eng.draw(car.shape, car.parking_shape);  
		car.draw_circe(eng);
		eng.window.display();
		eng.window.clear();
	}
}
