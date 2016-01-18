#include "FactoryFlock.h"

FactoryFlock::FactoryFlock(int amount, sf::FloatRect bounds)
{

	for (int i = 0; i < amount; i++)
	{
		float randX = std::rand() % 5000;
		float randY = std::rand() % 3500;
		flock.push_back(new Factory(sf::Vector2f(randX, randY), sf::Vector2f(((std::rand() % 200) - 100) / 100.0f, ((std::rand() % 200) - 100) / 100.0f), bounds));
	}
}

void FactoryFlock::Update(float deltaTime, Pvector playerPos)
{
	//Update Flock
	for (int i = 0; i < flock.size(); i++)
	{
		if (flock[i]->GetState() == Factory::State::Wandering)
		{
			Pvector location(flock[i]->GetPosition().x, flock[i]->GetPosition().y);
			for (int j = 0; j < flock.size(); j++)
			{
				Pvector otherLocation(flock[j]->GetPosition().x, flock[j]->GetPosition().y);
				float distance = location.distance(otherLocation);
				if (distance > 0 && distance < 100)
				{
					flock[i]->SetState(Factory::State::Flocking);
					flock[j]->SetState(Factory::State::Flocking);
				}
			}
		}

		flock[i]->Update(deltaTime, flock, playerPos);
	}
}

void FactoryFlock::Draw(sf::RenderWindow* window)
{
	//Draw Flock
	for (int i = 0; i < flock.size(); i++)
	{
		flock[i]->Draw(window);
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
			flockBounds.push_back(flock[i]->GetBounds());
		}
	}

	return flockBounds;
}