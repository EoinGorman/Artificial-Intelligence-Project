#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Factory.h"
#include <vector>

class FactoryFlock 
{
public:
	FactoryFlock(int amount, sf::FloatRect bounds);
	void Update(float deltaTime, Pvector playerPos);
	void Draw(sf::RenderWindow* window);

	void DestroyShip(int index);
	std::vector<sf::Rect<float>> GetFactoryBounds();

private:
	std::vector<Factory*> flock;
};