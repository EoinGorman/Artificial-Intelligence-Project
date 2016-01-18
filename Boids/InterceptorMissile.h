#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class InterceptorMissile
{
public:
    InterceptorMissile();
    InterceptorMissile(sf::Vector2f pos, float angle, sf::FloatRect bounds, sf::Vector2f targetPos);

    void Update(float deltaTime, sf::Vector2f targetPos);
    void Draw(sf::RenderWindow* window);
    bool MarkedForDeletion();
    sf::Vector2f GetPosition();
    sf::Rect<float> GetBounds();

private:
    //Functions
    void Move(float deltaTime, sf::Vector2f targetPos);
    void CheckForDeletion(float deltaTime);

    //Variables
    float timer;
    bool marked;
    int m_width;
    int m_height;
    float m_speed;
    sf::Vector2f m_position;
    sf::Vector2f m_direction;
    sf::Sprite m_sprite;
    sf::Texture m_texture;
    sf::FloatRect m_bounds;	//level bounds
};