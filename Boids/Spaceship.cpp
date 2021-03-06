#include "Spaceship.h"
#include "Bullet.h"

//PUBLIC
Spaceship::Spaceship()
{
    m_radarTexture.loadFromFile("../Images/enemyRadarSprite.png");
    m_radarSprite.setTexture(m_radarTexture, true);
    m_radarSprite.setOrigin(m_radarSprite.getLocalBounds().width / 2, m_radarSprite.getLocalBounds().height / 2);

	m_texture.loadFromFile("../Images/Spaceship_1.png");
	m_sprite.setTexture(m_texture, true);
	m_width = m_sprite.getLocalBounds().width;
	m_height = m_sprite.getLocalBounds().height;
	m_speed = 0.02f;
	m_position = sf::Vector2f(0, 0);
	m_direction = sf::Vector2f(1, 0);
	m_bounds = sf::FloatRect(m_position.x, m_position.y, m_width, m_height);
	m_sprite.setOrigin(m_width / 2, m_height / 2);
    m_sprite.setPosition(m_position);
}

Spaceship::Spaceship(sf::Vector2f pos, sf::Vector2f dir, sf::FloatRect bounds)
{
    m_radarTexture.loadFromFile("../Images/enemyRadarSprite.png");
    m_radarSprite.setTexture(m_radarTexture, true);
    m_radarSprite.setOrigin(m_radarSprite.getLocalBounds().width / 2, m_radarSprite.getLocalBounds().height / 2);

	m_texture.loadFromFile("../Images/Spaceship_1.png");
	m_sprite.setTexture(m_texture, true);
	m_width = m_sprite.getLocalBounds().width;
	m_height = m_sprite.getLocalBounds().height;
	m_speed = 0.02f;
	m_position = pos;
	m_direction = dir;
	m_bounds = bounds;
	m_sprite.setOrigin(m_width / 2, m_height / 2);
    m_sprite.setPosition(m_position);
}

void Spaceship::Update(float deltaTime)
{
	WrapAroundScreen();
	Move(deltaTime);
}

void Spaceship::Draw(sf::RenderWindow* window)
{
	window->draw(m_sprite);
}

void Spaceship::DrawRadarImage(sf::RenderWindow* window)
{
    m_radarSprite.setPosition(m_position);
    window->draw(m_radarSprite);
}

sf::Vector2f Spaceship::GetPosition()
{
	return m_position;
}


//PRIVATE

void Spaceship::Move(float deltaTime)
{
	//"Space Friction"

	m_position += m_direction * m_speed * deltaTime;
	m_sprite.setPosition(m_position);
}

void Spaceship::WrapAroundScreen()
{
	//X axis
	if (m_position.x < m_bounds.left - m_width)
	{
		m_position.x = m_bounds.left + m_bounds.width + (m_width / 2);
	}

	else if (m_position.x > m_bounds.left + m_bounds.width + m_width)
	{
		m_position.x = m_bounds.left - (m_width / 2);
	}

	//Y axis
	if (m_position.y < m_bounds.top - m_height)
	{
		m_position.y = m_bounds.top + m_bounds.height + m_height / 2;
	}

	else if (m_position.y > m_bounds.top + m_bounds.height + m_height)
	{
		m_position.y = m_bounds.top - m_height / 2;
	}
}

sf::Rect<float> Spaceship::GetBounds()
{
    return m_sprite.getGlobalBounds();
}
