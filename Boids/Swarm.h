#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SwarmShip.h"
#include <vector>

class Swarm
{
public:
	Swarm(int amount, sf::FloatRect bounds);
	void Update(float deltaTime, Pvector targetPos);
	void Draw(sf::RenderWindow* window);

private:
	std::vector<SwarmShip*> swarm;
};