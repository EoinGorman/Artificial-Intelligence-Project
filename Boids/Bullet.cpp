#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Bullet.h"
#define PI 3.14159265
#define MaxSpeed 250

//PUBLIC
Bullet::Bullet()
{
	m_texture.loadFromFile("../Images/Bullet.png");
	m_sprite.setTexture(m_texture, true);
	m_width = m_sprite.getLocalBounds().width;
	m_height = m_sprite.getLocalBounds().height;
	m_speed = MaxSpeed;
	m_position = sf::Vector2f(0, 0);
	m_direction = sf::Vector2f(1, 0);
	m_bounds = sf::FloatRect(m_position.x, m_position.y, m_width, m_height);
	m_sprite.setRotation(0);
	offScreen = false;
}

Bullet::Bullet(sf::Vector2f pos, float angle, sf::FloatRect bounds, float speed)
{
	m_texture.loadFromFile("../Images/Bullet.png");
	m_sprite.setTexture(m_texture, true);
	m_width = m_sprite.getLocalBounds().width;
	m_height = m_sprite.getLocalBounds().height;
	m_speed = MaxSpeed + speed;
	m_position = pos - sf::Vector2f(m_width/2, m_height/2);
	m_direction = m_direction = sf::Vector2f(cos(angle*PI / 180), sin(angle*PI / 180));;
	m_position += m_direction * 10.0f;
	m_bounds = bounds;
	m_sprite.setRotation(angle);
	offScreen = false;
}

void Bullet::Update(float deltaTime)
{
	if (!offScreen)
	{
		CheckBounds();
		Move(deltaTime);
	}
}

void Bullet::Draw(sf::RenderWindow* window)
{
	if (!offScreen)
	{
		window->draw(m_sprite);
	}
}


bool Bullet::OutOfBounds()
{
	return offScreen;
}

sf::Vector2f Bullet::GetPosition()
{
	return m_position;
}


//PRIVATE

void Bullet::Move(float deltaTime)
{
	m_position += m_direction * m_speed * deltaTime;
	m_sprite.setPosition(m_position);
}

bool Bullet::MarkedForDeletion()
{
	return offScreen;
}

void Bullet::CheckBounds()
{
	//X axis
	if (m_position.x < m_bounds.left - m_width)
	{
		offScreen = true;
	}

	else if (m_position.x > m_bounds.left + m_bounds.width + m_width)
	{
		offScreen = true;
	}

	//Y axis
	if (m_position.y < m_bounds.top - m_height)
	{
		offScreen = true;
	}

	else if (m_position.y > m_bounds.top + m_bounds.height + m_height)
	{
		offScreen = true;
	}
}


sf::Rect<float> Bullet::GetBounds()
{
	return m_sprite.getGlobalBounds();
}
