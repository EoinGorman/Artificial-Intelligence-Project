#ifndef SWARM_SHIP_H
#define SWARM_SHIP_H

#include <vector>
#include "Spaceship.h"
#include "Pvector.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class SwarmShip : public Spaceship
{
public:
	//Functions
	enum State
	{
		Swarming = 0,
		Intercepting = 1
	};

	SwarmShip(sf::Vector2f pos, sf::Vector2f dir, sf::FloatRect bounds);
	void Update(float deltaTime, vector<SwarmShip*> otherShips, Pvector targetPos);
	State GetState();

	//Variables

private:
	//Functions
	void Move();
	float Angle();
	void ApplyForce(Pvector force);
	void Swarm(vector<SwarmShip*> otherShips, Pvector targetPos);
	void Intercept(Pvector targetPos);

	//Variables
	State currentState;
	Pvector velocity;
	Pvector acceleration;
	float maxSpeed;
	float maxForce;
};

#endif