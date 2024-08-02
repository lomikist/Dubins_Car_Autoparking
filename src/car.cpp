#include <cmath>
#include "car.hpp"
#include "helpers.hpp"
#include "path_manager.hpp"

#include <iostream>

Car::Car()
{
    _speed = CAR_SPEED;
    sf::Vector2f size(CAR_WIDTH, CAR_HEIGHT);
    _rect.setSize(size);
    _rect.setOrigin(size / 2.0f);
    _rect.setPosition(CAR_POS_X, CAR_POS_Y);
    _rect.setRotation(CAR_ROTATION);
    _circle.setRadius(RADIUS);
    _circle.setOrigin(RADIUS, RADIUS);

    // Colors
    _rect.setFillColor(sf::Color(CAR_RED, CAR_GREEN, CAR_BLUE));
    _circle.setFillColor(sf::Color::Black);
    _circle.setOutlineColor(sf::Color(30, 144, 255));
    _circle.setOutlineThickness(2);
}

Car::~Car()
{}

void Car::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_rect, states);
    target.draw(_circle, states);

    // **************** Testing *************** //
    target.draw(carCirclePoint);
    target.draw(spotCirclePoint);
}

void Car::processMove(float elapsedTime, ParkingSpot& parkingSpot)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        _isAutoParkingOn = false;
    else
        _isAutoParkingOn = true;

    if (_isAutoParkingOn)
        processAutoParking(elapsedTime, parkingSpot);
    else
        processUserControl(elapsedTime);
}

void Car::processAutoParking(float elapsedTime, ParkingSpot& parkingSpot)
{
    Path& shortestPath = _pathManager.findShortestPath(
                                                _rect,
                                                parkingSpot.getRect(), 
                                                _circle.getRadius()
                                                );
    _circle.setPosition(shortestPath.carCirclePos);
    parkingSpot.getCircle().setPosition(shortestPath.spotCirclePos);

    auto [Cx1, Cy1] = _rect.getPosition();
    auto [Sx1, Sy1] = parkingSpot.getRect().getPosition();
    auto [Tx1, Ty1] = shortestPath.carTangentPoint;
    auto [Tx2, Ty2] = shortestPath.spotTangentPoint;
    float epsilion = 0.1f;

    // std::cout << "Coords: " << Cx1 << "  " << Cy1 << "  " << Tx1 << "  " << Ty1 << std::endl;
    std::cout << "Coords: " << fabs(Cx1 - Tx2) << "  " << fabs(Cy1 - Ty2) << std::endl;
    // std::cout << "Distance: " << calcDistance(_circle.getPosition().x, _circle.getPosition().y, Cx1, Cy1) << std::endl;

    if (shortestPath.state == Path::State::CarCircle)
    {
        if (fabs(Cx1 - Tx1) > epsilion || fabs(Cy1 - Ty1) > epsilion)
        {
            if (shortestPath.type == Path::Type::LSL || shortestPath.type == Path::Type::LSR)    
                moveCircle(elapsedTime, MoveType::Left);
            else
                moveCircle(elapsedTime, MoveType::Right);
        }
        else
            shortestPath.state = Path::State::Straight;
    }
    else if (shortestPath.state == Path::State::Straight)
    {
        if (fabs(Cx1 - Tx2) > epsilion || fabs(Cy1 - Ty2) > epsilion)
            moveStraight(elapsedTime);
        else
            shortestPath.state = Path::State::SpotCircle;
    }
    else if (shortestPath.state == Path::State::SpotCircle)
    {
        if (fabs(Cx1 - Sx1) > epsilion || fabs(Cy1 - Sy1) > epsilion)
        {
            if (shortestPath.type == Path::Type::LSL || shortestPath.type == Path::Type::RSL)    
                moveCircle(elapsedTime, MoveType::Left);
            else
                moveCircle(elapsedTime, MoveType::Right);
        }
        else
            shortestPath.state = Path::State::Stop;
    }











    // **************** Testing *************** //
    carCirclePoint.setPosition(shortestPath.carTangentPoint);
    spotCirclePoint.setPosition(shortestPath.spotTangentPoint);
    carCirclePoint.setFillColor(sf::Color::Green);
    spotCirclePoint.setFillColor(sf::Color::Green);
    carCirclePoint.setRadius(3);
    spotCirclePoint.setRadius(3);
}

void Car::processUserControl(float elapsedTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            moveCircle(elapsedTime, Car::MoveType::Left);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            moveCircle(elapsedTime, Car::MoveType::Right);
        else
            moveStraight(elapsedTime);
    }
}

void Car::moveStraight(float elapsedTime)
{
    float angleRadian = degreeToRadian(_rect.getRotation());
    float offsetX = elapsedTime * _speed * cosf(angleRadian);
    float offsetY = elapsedTime * _speed * sinf(angleRadian);
    _rect.move(offsetX, offsetY);
}

void Car::moveCircle(float elapsedTime, MoveType moveType)
{
    _angVelocity = elapsedTime * radianToDegree(_speed / _circle.getRadius());
    if (moveType == MoveType::Left)
        _rect.rotate(-_angVelocity);
    else
        _rect.rotate(_angVelocity);
    moveStraight(elapsedTime);
}

bool Car::isAutoParkingOn() const
{
    return _isAutoParkingOn;
}
