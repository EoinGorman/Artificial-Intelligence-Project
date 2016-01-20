#pragma once
#include "Spaceship.h"
#include "InterceptorMissile.h"

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
	void Update(float deltaTime, std::vector<Factory*> flock, Pvector playerPos);
    void Factory::Draw(sf::RenderWindow* window);
	State GetState();
	void SetState(State newState);
    bool DamageShip();
    void DestroyMissile(int index);
    std::vector<sf::FloatRect> GetMissileBounds();

	//Variables

private:
	//Functions

    void CheckForShoot(float deltaTime, Pvector playerPos);
	void Move(float deltaTime);
	void Wander(float deltaTime, Pvector playerPos);
	void Flock(std::vector<Factory*> flock, float deltaTime, Pvector playerPos);
	// Three Laws that boids follow
	Pvector Separation(vector<Factory*> flock, Pvector playerPos);
	Pvector Alignment(vector<Factory*> flock);
	Pvector Cohesion(vector<Factory*> flock);
	Pvector Seek(Pvector v);
	float Angle();
	void ApplyForce(Pvector force);
    void Factory::Shoot(Pvector playerPos);

	//Variables
    int hitsTaken;
    std::vector<InterceptorMissile*> missiles;
    float reloadTimer;
	State currentState;
	Pvector velocity;
	Pvector acceleration;
	float maxForce;
	float wanderTimer;
	float wanderTime;
};