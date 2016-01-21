#pragma once

#include "Asteroid.h"

class AsteroidField
{
public:
    AsteroidField(int amount, sf::FloatRect bounds);
    void Update(float deltaTime);
    void Draw(sf::RenderWindow* window);
    std::vector<sf::Rect<float>> GetBounds();
    std::vector <std::tuple<float, Pvector>> GetSizeAndPosition();

private:
    sf::Vector2f GetValidScale();
    std::vector<Asteroid*> m_asteroids;
};