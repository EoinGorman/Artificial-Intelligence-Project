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
	void Update(float deltaTime, std::vector<Factory*> flock);
	State GetState();
	void SetState(State newState);
	sf::Rect<float> GetBounds();

	//Variables

private:
	//Functions
	void Move(float deltaTime);
	void Wander(float deltaTime);
	void Flock(std::vector<Factory*> flock, float deltaTime);
	// Three Laws that boids follow
	Pvector Separation(vector<Factory*> flock);
	Pvector Alignment(vector<Factory*> flock);
	Pvector Cohesion(vector<Factory*> flock);
	Pvector Seek(Pvector v);
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