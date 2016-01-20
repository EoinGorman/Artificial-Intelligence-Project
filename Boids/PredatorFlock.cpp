#include "PredatorFlock.h"

PredatorFlock::PredatorFlock(int amount, sf::FloatRect bounds)
{

	for (int i = 0; i < amount; i++)
	{
		float randX = std::rand() % 5000;
		float randY = std::rand() % 3500;
		flock.push_back(new Predator(sf::Vector2f(randX, randY), sf::Vector2f(((std::rand() % 200) - 100) / 100.0f, ((std::rand() % 200) - 100) / 100.0f), bounds));
	}
}

void PredatorFlock::Update(float deltaTime, Pvector playerPos)
{
	//Update Flock
	for (int i = 0; i < flock.size(); i++)
	{
		if (flock[i]->GetState() == Predator::State::Seeking)
		{
			Pvector location(flock[i]->GetPosition().x, flock[i]->GetPosition().y);
			for (int j = 0; j < flock.size(); j++)
			{
				Pvector otherLocation(flock[j]->GetPosition().x, flock[j]->GetPosition().y);
				float distance = location.distance(otherLocation);
				if (distance > 0 && distance < 100)
				{
					flock[i]->SetState(Predator::State::Flocking);
					flock[j]->SetState(Predator::State::Flocking);
				}
			}
		}

		flock[i]->Update(deltaTime, flock, playerPos);
	}
}

void PredatorFlock::Draw(sf::RenderWindow* window)
{
	//Draw Flock
	for (int i = 0; i < flock.size(); i++)
	{
		flock[i]->Draw(window);
	}
}

void PredatorFlock::DestroyShip(int index)
{
	delete flock[index];
	flock.erase(flock.begin() + index);
}

std::vector<sf::Rect<float>> PredatorFlock::GetPredatorBounds()
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