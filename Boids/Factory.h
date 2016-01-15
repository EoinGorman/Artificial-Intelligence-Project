#pragma once
#include "Spaceship.h"

class Factory : public Spaceship
{
public:
	//Functions
	enum State
	{
		Wandering = 0,
		Flocking = 1,
	};

	Factory(sf::Vector2f pos, sf::Vector2f dir, sf::FloatRect bounds);
	void Update(float deltaTime, vector<Factory*> otherShips);
	State GetState();
	void SetState(State newState);
	sf::Rect<float> GetBounds();

	//Variables

private:
	//Functions
	void Move(float deltaTime);
	void Wander(float deltaTime);
	void Flock(float deltaTime);
	// Three Laws that boids follow
	Pvector Separation(vector<Factory*> Boids);
	Pvector Alignment(vector<Factory*> Boids);
	Pvector Cohesion(vector<Factory*> Boids);
	float Angle();
	void ApplyForce(Pvector force);

	//Variables
	State currentState;
	Pvector velocity;
	Pvector acceleration;
	float maxForce;
	float wanderTimer;
	float wanderTime;
};