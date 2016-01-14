#include "Swarm.h"

Swarm::Swarm(int amount, sf::FloatRect bounds)
{
	for (int i = 0; i < amount; i++)
	{
		SwarmShip* ship = new SwarmShip(sf::Vector2f(0, 0), sf::Vector2f(0, 0), bounds);
		swarm.push_back(ship);
	}
}

void Swarm::Update(float deltaTime, Pvector targetPos)
{
	for (int i = 0; i < swarm.size(); i++)
	{
		swarm[i]->Update(deltaTime, swarm, targetPos);
	}
		
	for (int i = 0; i < swarm.size(); i++)
	{
		if (swarm[i]->GetState() == SwarmShip::State::Intercepting)
		{
			swarm.erase(swarm.begin() + i);
			break;
		}
	}
}

void Swarm::Draw(sf::RenderWindow* window)
{
	for (int i = 0; i < swarm.size(); i++)
	{
		swarm[i]->Draw(window);
	}
}