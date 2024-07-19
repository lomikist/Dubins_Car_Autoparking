#ifndef HELPERS_HPP
#define HELPERS_HPP

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
#define CAR_SPEED 100
#define AUTO_PARKING false

// Car color defines
#define CAR_RED 100
#define CAR_GREEN 150
#define CAR_BLUE 25

// Parking spot defines
#define SPOT_POS_X 550
#define SPOT_POS_Y 550
#define SPOT_ROTATION 0

// Parking spot color defines
#define SPOT_RED 255
#define SPOT_GREEN 0
#define SPOT_BLUE 0

// General defines
#define RADIUS 50

constexpr float pi = 3.14159f;

// Util functions
float radianToDegree(float radian);
float degreeToRadian(float degree);
void setCircleCenterPos(const sf::RectangleShape& rect, sf::CircleShape& circle);

#endif  /* HELPERS_HPP */