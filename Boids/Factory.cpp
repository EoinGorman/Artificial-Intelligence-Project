/*//Functions
enum State
{
	Wandering = 0,
	Flocking = 1,
};

Factory(sf::Vector2f pos, sf::Vector2f dir, sf::FloatRect bounds);
void Update(float deltaTime, vector<Factory*> otherShips, Pvector targetPos);
State GetState();
void SetState(State newState);
sf::Rect<float> GetBounds();

//Variables

private:
	//Functions
	void Move(float deltaTime);
	float Angle();
	void ApplyForce(Pvector force);

	//Variables
	State currentState;
	Pvector velocity;
	Pvector acceleration;
	float maxForce;
	*/

#include "Factory.h"

Factory::Factory(sf::Vector2f pos, sf::Vector2f dir, sf::FloatRect bounds)
	: Spaceship(pos, dir, bounds)
{
	wanderTime = (std::rand() % 5000) / 1000.0f;
	wanderTimer = 0;
	m_speed = 5;
	currentState = State::Wandering;

	m_texture.loadFromFile("../Images/Spaceship_3.png");
	m_sprite.setTexture(m_texture, true);
	m_width = m_sprite.getLocalBounds().width;
	m_height = m_sprite.getLocalBounds().height;
	m_sprite.setOrigin(m_width / 2, m_height / 2);

	m_direction = sf::Vector2f(((std::rand() % 100) - 100) / 100.0f, ((std::rand() % 100) - 100) / 100.0f);
	m_sprite.setRotation(atan2(m_direction.y, m_direction.x));
}

void Factory::Update(float deltaTime, vector<Factory*> otherShips)
{
	switch (currentState)
	{
	case Wandering:
		Wander(deltaTime);
		break;
	case Flocking:
		break;
	}

	WrapAroundScreen();
}

Factory::State Factory::GetState()
{
	return currentState;
}
void Factory::SetState(State newState)
{
	currentState = newState;
}

sf::Rect<float> Factory::GetBounds()
{
	return m_sprite.getGlobalBounds();
}

void Factory::Move(float deltaTime)
{

}


void Factory::Flock(float deltaTime)
{

}

// Three Laws that boids follow
Pvector Factory::Separation(vector<Factory*> Boids)
{

}

Pvector Factory::Alignment(vector<Factory*> Boids)
{

}
Pvector Factory::Cohesion(vector<Factory*> Boids)
{

}

void Factory::Wander(float deltaTime)
{
	m_speed = 70;
	wanderTimer += deltaTime;
	if (wanderTimer >= wanderTime)
	{
		wanderTime = (std::rand() % 5000) / 1000.0f;
		wanderTimer = 0;

		m_direction = sf::Vector2f(((std::rand() % 100) - 100) / 100.0f, ((std::rand() % 100) - 100) / 100.0f);
		m_sprite.setRotation(atan2(m_direction.y, m_direction.x) * 180 / PI);
	}
	Spaceship::Move(deltaTime);
}

float Factory::Angle()
{
	float angle = (float)(atan2(velocity.y, velocity.x) * 180 / PI);
	return angle;
}

void Factory::ApplyForce(Pvector force)
{
	acceleration.addVector(force);
}