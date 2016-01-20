#pragma once
#include "Spaceship.h"
#include "InterceptorMissile.h"

class Predator : public Spaceship
{
public:
	//Functions
	enum State
	{
		Seeking = 0,
		Flocking = 1,
	};

	Predator(sf::Vector2f pos, sf::Vector2f dir, sf::FloatRect bounds);
	void Update(float deltaTime, std::vector<Predator*> flock, Pvector playerPos);
	void Predator::Draw(sf::RenderWindow* window);
	State GetState();
	void SetState(State newState);
	sf::Rect<float> GetBounds();

	//Variables

private:
	//Functions

	void CheckForShoot(float deltaTime, Pvector playerPos);
	void Move(float deltaTime);
	Pvector Finding(float deltaTime, Pvector playertPos);
	void Flock(std::vector<Predator*> flock, float deltaTime, Pvector playerPos);
	// Three Laws that boids follow
	Pvector Separation(vector<Predator*> flock, Pvector playerPos);
	Pvector Alignment(vector<Predator*> flock);
	Pvector Cohesion(float deltaTime,vector<Predator*> flock);
	Pvector Seek(float deltaTime,Pvector v);
	float Angle();
	void ApplyForce(Pvector force);
	void Predator::Shoot(Pvector playerPos);

	//Variables
	std::vector<InterceptorMissile*> missiles;
	float reloadTimer;
	State currentState;
	Pvector velocity;
	Pvector acceleration;
	float maxForce;
	float wanderTimer;
	float wanderTime;
};