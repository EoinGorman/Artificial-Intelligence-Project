#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "InputManager.h"
#include "Bullet.h"
#include "Spaceship.h"
#include "Playership.h"
#define MaxSpeed 450

Playership::Playership(sf::Vector2f pos, sf::Vector2f dir, sf::FloatRect bounds)
	: Spaceship(pos, dir, bounds)
{
    m_radarTexture.loadFromFile("../Images/playerRadarSprite.png");
    m_radarSprite.setTexture(m_radarTexture, true);
    m_radarSprite.setOrigin(m_radarSprite.getLocalBounds().width / 2, m_radarSprite.getLocalBounds().height / 2);

	m_rotation = 0;
	m_texture.loadFromFile("../Images/Spaceship_2.png");
	m_sprite.setTexture(m_texture, true);
	m_width = m_sprite.getLocalBounds().width;
	m_height = m_sprite.getLocalBounds().height;
	m_sprite.setOrigin(sf::Vector2f(m_width / 2, m_height / 2));

	m_speed = 0.0f;
}

void Playership::Update(float deltaTime)
{
		
	if (InputManager::GetInstance()->IsKeyDown(sf::Keyboard::Space))
	{
		m_bullets.push_back(new Bullet(m_position, m_rotation, m_bounds, abs(m_speed)));
	}

	if (InputManager::GetInstance()->IsKeyHeld(sf::Keyboard::Left))
	{
		//m_direction
		m_rotation -= 120 * deltaTime;
	}

	else if (InputManager::GetInstance()->IsKeyHeld(sf::Keyboard::Right))
	{
		//m_direction
		m_rotation += 120 * deltaTime;
	}

	if (InputManager::GetInstance()->IsKeyHeld(sf::Keyboard::Up))
	{
		//m_direction
		if (m_speed < MaxSpeed)
			m_speed += 10;
		else
			m_speed = MaxSpeed;
	}

	else if (InputManager::GetInstance()->IsKeyHeld(sf::Keyboard::Down))
	{
		//m_direction

		if (m_speed > -MaxSpeed)
			m_speed -= 10;
		else
			m_speed = -MaxSpeed;
	}


	for (int i = 0; i < m_bullets.size(); i++)
	{
		if (m_bullets.at(i)->OutOfBounds())
		{
			delete m_bullets.at(i);
			m_bullets.erase(m_bullets.begin() + i);
			break;
		}
		else
		{
			m_bullets.at(i)->Update(deltaTime);
		}
	}

	m_sprite.setRotation(m_rotation);
	m_direction = sf::Vector2f(cos(m_rotation*PI / 180), sin(m_rotation*PI / 180));

	if (m_speed > 0)
	{
		m_speed -= 50 * deltaTime;
	}
	else if (m_speed < 0)
	{
		m_speed += 50 * deltaTime;
	}
	Spaceship::Update(deltaTime);
}


void Playership::Draw(sf::RenderWindow* window)
{
	Spaceship::Draw(window);
	for (int i = 0; i < m_bullets.size(); i++)
	{
		m_bullets.at(i)->Draw(window);
	}
}

void Playership::DestroyBullet(int index)
{
	delete m_bullets.at(index);
	m_bullets.erase(m_bullets.begin() + index);
}


std::vector<sf::Rect<float>> Playership::GetBulletBounds()
{
	std::vector<sf::Rect<float>> bulletBounds;
	if (m_bullets.size() > 0)
	{
		for (int i = 0; i < m_bullets.size(); i++)
		{
			bulletBounds.push_back(m_bullets[i]->GetBounds());
		}
	}

	return bulletBounds;
}