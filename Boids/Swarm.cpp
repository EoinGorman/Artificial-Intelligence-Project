#include "Swarm.h"
#define InterceptDistance 250

Swarm::Swarm(int amount, sf::FloatRect bounds)
{
	for (int i = 0; i < amount; i++)
	{
		float randX = std::rand() % 5000;
		float randY = std::rand() % 3500;
		swarm.push_back(new SwarmShip(sf::Vector2f(randX, randY), sf::Vector2f(0, 0), bounds));
	}
}

void Swarm::Update(float deltaTime, Pvector targetPos)
{
	//Update SwarmShips
	for (int i = 0; i < swarm.size(); i++)
	{
		swarm[i]->Update(deltaTime, swarm, targetPos); 
		
		//Change States
		if (swarm[i]->GetState() == SwarmShip::State::Intercepting)
		{
			if (Pvector(swarm[i]->GetPosition().x, swarm[i]->GetPosition().y).distance(targetPos) > InterceptDistance)
			{
				swarm[i]->SetState(SwarmShip::State::Swarming);
			}
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

void Swarm::DrawRadarImage(sf::RenderWindow* window)
{
    for (int i = 0; i < swarm.size(); i++)
    {
        swarm[i]->DrawRadarImage(window);
    }
}

void Swarm::DestroyShip(int index)
{
	delete swarm[index];
	swarm.erase(swarm.begin() + index);
}

std::vector<sf::Rect<float>> Swarm::GetSwarmBounds()
{
	std::vector<sf::Rect<float>> swarmBounds;
	if (swarm.size() > 0)
	{
		for (int i = 0; i < swarm.size(); i++)
		{
			swarmBounds.push_back(swarm[i]->GetBounds());
		}
	}

	return swarmBounds;
}