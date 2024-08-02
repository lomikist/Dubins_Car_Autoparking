#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <SFML/Graphics.hpp>

// Application defines
#define APP_NAME "Dubins Car Automatic Parking"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

// Car defines
#define CAR_WIDTH 50
#define CAR_HEIGHT 25
#define CAR_POS_X 250
#define CAR_POS_Y 250
#define CAR_ROTATION 0
#define CAR_SPEED 5

// Car color defines
#define CAR_RED 100
#define CAR_GREEN 150
#define CAR_BLUE 25

// Parking spot defines
#define SPOT_POS_X 600
#define SPOT_POS_Y 250
#define SPOT_ROTATION 120

// Parking spot color defines
#define SPOT_RED 255
#define SPOT_GREEN 0
#define SPOT_BLUE 0

// General defines
#define RADIUS 50

constexpr float pi = 3.14159f;

// Typedefs
typedef sf::CircleShape Circle;
typedef sf::RectangleShape Rect;

// Util functions
float radianToDegree(float radian);
float degreeToRadian(float degree);
float calcDistance(float x1, float y1, float x2, float y2);
float calcDistance(const sf::Vector2f& point1, const sf::Vector2f& point2);
sf::Vector2f getCircleCenterPos(const Rect& rect, float radius, int moveType);

#endif  /* HELPERS_HPP */