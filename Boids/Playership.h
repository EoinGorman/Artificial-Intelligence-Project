#ifndef PLAYERSHIP 
#define PLAYERSHIP
#include "Bullet.h"

class Playership : public Spaceship
{
public:
	//Functions
	Playership(sf::Vector2f pos, sf::Vector2f dir, sf::FloatRect bounds);
	void Update(float deltaTime);
	void Draw(sf::RenderWindow* window);

	void DestroyBullet(int index);
	std::vector<sf::Rect<float>> GetBulletBounds();

	//Variables

private:
	//Functions

	//Variables
	float m_rotation;	//Keep m_rotation in degrees
	std::vector<Bullet*> m_bullets;
};

#endif