#include "InterceptorMissile.h"

#define PI 3.14159265
#define MaxSpeed 450
#define lifetime 10

//PUBLIC
InterceptorMissile::InterceptorMissile()
{
    m_texture.loadFromFile("../Images/Missile.png");
    m_sprite.setTexture(m_texture, true);
    m_width = m_sprite.getLocalBounds().width;
    m_height = m_sprite.getLocalBounds().height;
    m_speed = MaxSpeed;
    m_position = sf::Vector2f(0, 0);
    m_direction = sf::Vector2f(1, 0);
    m_bounds = sf::FloatRect(m_position.x, m_position.y, m_width, m_height);
    m_sprite.setRotation(0);
    timer = 0;
    marked = false;
}

InterceptorMissile::InterceptorMissile(sf::Vector2f pos, float angle, sf::FloatRect bounds, sf::Vector2f targetPos)
{
    m_texture.loadFromFile("../Images/Missile.png");
    m_sprite.setTexture(m_texture, true);
    m_width = m_sprite.getLocalBounds().width;
    m_height = m_sprite.getLocalBounds().height;
    m_speed = MaxSpeed;
    m_position = pos - sf::Vector2f(m_width / 2, m_height / 2);
    m_direction = targetPos - m_position;
    //normalise direction
    float mag = sqrt(m_direction.x * m_direction.x + m_direction.y * m_direction.y); //Magnitude of vector formula
    m_direction /= mag;

    m_position += m_direction * 10.0f;
    m_bounds = bounds;
    m_sprite.setRotation(angle);
    timer = 0;
    marked = false;
}

void InterceptorMissile::Update(float deltaTime, sf::Vector2f targetPos)
{
    if (!marked)
    {
        CheckForDeletion(deltaTime);
        Move(deltaTime, targetPos);
    }
}

void InterceptorMissile::Draw(sf::RenderWindow* window)
{
    if (!marked)
    {
        window->draw(m_sprite);
    }
}


bool InterceptorMissile::MarkedForDeletion()
{
    return marked;
}

sf::Vector2f InterceptorMissile::GetPosition()
{
    return m_position;
}


//PRIVATE

void InterceptorMissile::Move(float deltaTime, sf::Vector2f targetPos)
{
    m_direction = targetPos - m_position;
    //normalise direction
    float mag = sqrt(m_direction.x * m_direction.x + m_direction.y * m_direction.y); //Magnitude of vector formula
    m_direction /= mag;

    m_position += m_direction * m_speed * deltaTime;
    m_sprite.setPosition(m_position);
}

void InterceptorMissile::CheckForDeletion(float deltaTime)
{
    //Check Bounds
    //X axis
    if (m_position.x < m_bounds.left - m_width)
    {
        marked = true;
    }

    else if (m_position.x > m_bounds.left + m_bounds.width + m_width)
    {
        marked = true;
    }

    //Y axis
    if (m_position.y < m_bounds.top - m_height)
    {
        marked = true;
    }

    else if (m_position.y > m_bounds.top + m_bounds.height + m_height)
    {
        marked = true;
    }

    //Update and Check Timer
    timer += deltaTime;
    if (timer >= lifetime)
    {
        marked = true;
    }
}


sf::Rect<float> InterceptorMissile::GetBounds()
{
    return m_sprite.getGlobalBounds();
}