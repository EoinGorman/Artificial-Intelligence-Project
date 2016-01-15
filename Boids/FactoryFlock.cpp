#include "FactoryFlock.h"

FactoryFlock::FactoryFlock(int amount, sf::FloatRect bounds)
{

	for (int i = 0; i < amount; i++)
	{
		float randX = std::rand() % 5000;
		float randY = std::rand() % 3500;
		//flock.push_back(new Factory(sf::Vector2f(randX, randY), sf::Vector2f(0, 0), bounds));
	}
}

void FactoryFlock::Update(float deltaTime)
{
	//Update Flock
	for (int i = 0; i < flock.size(); i++)
	{
		//flock[i]->Update(deltaTime, swarm, targetPos);
	}
}

void FactoryFlock::Draw(sf::RenderWindow* window)
{
	//Draw Flock
	for (int i = 0; i < flock.size(); i++)
	{
		//flock[i]->Draw(window);
	}
}

void FactoryFlock::DestroyShip(int index)
{
	delete flock[index];
	flock.erase(flock.begin() + index);
}

std::vector<sf::Rect<float>> FactoryFlock::GetFactoryBounds()
{
	std::vector<sf::Rect<float>> flockBounds;
	if (flock.size() > 0)
	{
		for (int i = 0; i < flock.size(); i++)
		{
			//flockBounds.push_back(flock[i]->GetBounds());
		}
	}

	return flockBounds;
}