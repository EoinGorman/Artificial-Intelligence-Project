/*
public:
Asteroid(sf::Vector2f position, sf::Vector2f direction, sf::Vector2f scale, sf::FloatRect bounds);
void Update(float deltaTime);
void Draw(sf::RenderWindow* window);
sf::FloatRect GetBounds();

private:
void Move();

float m_speed;
sf::FloatRect m_bounds;
sf::Vector2f m_scale;
sf::Vector2f m_position;
sf::Vector2f m_direction;
sf::Texture m_texture;
sf::Sprite m_sprite;
*/

#include "Asteroid.h"

Asteroid::Asteroid(sf::Vector2f position, sf::Vector2f direction, sf::Vector2f scale, sf::FloatRect bounds)
{
    m_position = position;
    m_direction = direction;
    m_scale = scale;
    m_bounds = bounds;

    m_texture.loadFromFile("../Images/asteroid.png");
    m_sprite.setTexture(m_texture);
    m_width = m_sprite.getLocalBounds().width;
    m_height = m_sprite.getLocalBounds().height;
    m_sprite.setOrigin(m_width / 2, m_height / 2);
    m_sprite.setRotation(std::rand() % 360);
    m_sprite.setScale(m_scale);

    m_sprite.setPosition(m_position);
    m_speed = std::rand() % 500;
}

void Asteroid::Update(float deltaTime)
{
    Move(deltaTime);
    WrapAroundScreen();
}

void Asteroid::Draw(sf::RenderWindow* window)
{
    window->draw(m_sprite);
}

sf::FloatRect Asteroid::GetBounds()
{
    return m_sprite.getGlobalBounds();
}

void Asteroid::Move(float deltaTime)
{
    m_position += m_direction * m_speed * deltaTime;
    m_sprite.setPosition(m_position);
}

void Asteroid::WrapAroundScreen()
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


std::tuple<float, Pvector> Asteroid::GetSizeAndPosition()
{
    return std::make_tuple<float, Pvector>(m_sprite.getGlobalBounds().width, Pvector(m_position.x, m_position.y));
}