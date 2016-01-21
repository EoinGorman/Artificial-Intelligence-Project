#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Factory.h"
#include "Playership.h"
#include <vector>

class FactoryFlock 
{
public:
	FactoryFlock(int amount, sf::FloatRect bounds);
	void Update(float deltaTime, Pvector playerPos, Playership* player, std::vector<std::tuple<float, Pvector>> asteroidSizeAndPos);
	void Draw(sf::RenderWindow* window);
    void DrawRadarImage(sf::RenderWindow* window);

    void DamageShip(int index);
	void DestroyShip(int index);
	std::vector<sf::Rect<float>> GetFactoryBounds();
    std::vector<sf::Rect<float>> GetMissileBounds();

private:
	std::vector<Factory*> flock;
    std::vector<InterceptorMissile*> missiles;
};