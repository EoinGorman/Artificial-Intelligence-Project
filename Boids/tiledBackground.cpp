#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "TiledBackground.h"

//PUBLIC
TiledBackground::TiledBackground()
{
	m_texture.loadFromFile("../Images/background.png");
	m_sprite.setTexture(m_texture, true);
	m_width = m_sprite.getLocalBounds().width;
	m_height = m_sprite.getLocalBounds().height;
	m_tiledBy = sf::Vector2f(1, 1);
	Tile();
}

TiledBackground::TiledBackground(sf::Vector2f tiledBy, sf::Vector2f screenSize)
{
	m_texture.loadFromFile("../Images/background.png");
	m_sprite.setTexture(m_texture, true);
	m_width = screenSize.x;
	m_height = screenSize.y;
	m_sprite.setScale(m_width / m_sprite.getLocalBounds().width, m_height / m_sprite.getLocalBounds().height);
	m_tiledBy = tiledBy;
	Tile();
}

void TiledBackground::Draw(sf::RenderWindow* window)
{
	for (int i = 0; i < m_tiledPositions.size(); i++)
	{
		m_sprite.setPosition(m_tiledPositions.at(i));
		window->draw(m_sprite);
	}
}

void TiledBackground::Tile()
{
	for (int i = 0; i < m_tiledBy.y; i++)
	{
		//loop through y axis

		for (int j = 0; j < m_tiledBy.x; j++)
		{
			//loop through x axis
			m_tiledPositions.push_back(sf::Vector2f(m_width * j, m_height * i));
		}
	}

	for (int i = 0; i < m_tiledPositions.size(); i++)
	{
		m_tiledPositions.at(i).x -= (m_tiledBy.x/2 * m_width) - (m_width / 2);
		m_tiledPositions.at(i).y -= (m_tiledBy.y/2 * m_height) - (m_height / 2);
	}
}