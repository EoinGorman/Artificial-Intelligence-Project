#pragma once

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Pvector.h"

class Asteroid
{
public:
    Asteroid(sf::Vector2f position, sf::Vector2f direction, sf::Vector2f scale, sf::FloatRect bounds);
    void Update(float deltaTime);
    void Draw(sf::RenderWindow* window);
    sf::FloatRect GetBounds();
    std::tuple<float, Pvector> GetSizeAndPosition();

private:
    void Move(float deltaTime);
    void WrapAroundScreen();

    float m_width;
    float m_height;
    float m_speed;
    sf::FloatRect m_bounds;
    sf::Vector2f m_scale;
    sf::Vector2f m_position;
    sf::Vector2f m_direction;
    sf::Texture m_texture;
    sf::Sprite m_sprite;
};