#include "Swarm.h"
#define InterceptDistance 250

Swarm::Swarm(int amount, sf::FloatRect bounds)
{
	
	for (int i = 0; i < amount; i++)
	{
		float randX = std::rand() % 100;
		float randY = std::rand() % 100;
		swarm.push_back(new SwarmShip(sf::Vector2f(randX, randY), sf::Vector2f(0, 0), bounds));
	}
}

void Swarm::Update(float deltaTime, Pvector targetPos)
{
	//Update SwarmShips
	for (int i = 0; i < swarm.size(); i++)
	{
		swarm[i]->Update(deltaTime, swarm, targetPos);
	}
		
	//Change States
	for (int i = 0; i < swarm.size(); i++)
	{
		if (swarm[i]->GetState() == SwarmShip::State::Intercepting)
		{
			if (Pvector(swarm[i]->GetPosition().x, swarm[i]->GetPosition().y).distance(targetPos) > InterceptDistance)
			{
				swarm[i]->SetState(SwarmShip::State::Swarming);
			}
			//swarm.erase(swarm.begin() + i);
			//break;
		}

		else
		{
			if (Pvector(swarm[i]->GetPosition().x, swarm[i]->GetPosition().y).distance(targetPos) < InterceptDistance)
			{
				swarm[i]->SetState(SwarmShip::State::Intercepting);
			}
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