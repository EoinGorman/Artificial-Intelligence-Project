#pragma once
#include "Spaceship.h"
#include "Bullet.h"

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
	void Update(float deltaTime, std::vector<Predator*> flock, Pvector playerPos, std::vector<std::tuple<float, Pvector>> asteroidSizeAndPos);
	void Predator::Draw(sf::RenderWindow* window);
	State GetState();
	void SetState(State newState);
	std::vector <sf::FloatRect> GetBulletBounds();
	void DestroyBullet(int index);
	//Variables

private:
	//Functions

	void CheckForShoot(float deltaTime, Pvector playerPos);
	void Move(float deltaTime);
	Pvector Finding(float deltaTime, Pvector playertPos, std::vector<std::tuple<float, Pvector>> asteroidSizeAndPos);
	void Flock(std::vector<Predator*> flock, float deltaTime, Pvector playerPos, std::vector<std::tuple<float, Pvector>> asteroidSizeAndPos);
	// Three Laws that boids follow
	Pvector Separation(vector<Predator*> flock, Pvector playerPos, std::vector<std::tuple<float, Pvector>> asteroidSizeAndPos);
	Pvector Alignment(vector<Predator*> flock);
	Pvector Cohesion(float deltaTime,vector<Predator*> flock);
	Pvector Seek(float deltaTime,Pvector v);
	float Angle();
	void ApplyForce(Pvector force);
	void Predator::Shoot(Pvector playerPos);
	float shootThePlayer(Pvector playerPos);
	//Variables
	std::vector<Bullet*> missiles;
	float reloadTimer;
	State currentState;
	Pvector velocity;
	Pvector acceleration;
	float maxForce;
	float wanderTimer;
	float wanderTime;

};