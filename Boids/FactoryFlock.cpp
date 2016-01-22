#include "FactoryFlock.h"
#define PredatorCreationTime 5

FactoryFlock::FactoryFlock(int amount, sf::FloatRect bounds)
{
    m_bounds = bounds;
	for (int i = 0; i < amount; i++)
	{
		float randX = std::rand() % 5000;
		float randY = std::rand() % 3500;
		flock.push_back(new Factory(sf::Vector2f(randX, randY), sf::Vector2f(((std::rand() % 200) - 100) / 100.0f, ((std::rand() % 200) - 100) / 100.0f), m_bounds));
	}
    predatorFlock = PredatorFlock(0, m_bounds);
    timer = PredatorCreationTime;
}

void FactoryFlock::Update(float deltaTime, Pvector playerPos, Playership* player, std::vector<std::tuple<float, Pvector>> asteroidSizeAndPos)
{
    SpawnTimer(deltaTime);
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

		flock[i]->Update(deltaTime, flock, playerPos, asteroidSizeAndPos);

        //Collision with interceptor missiles
        std::vector<sf::FloatRect> interceptorMissileBounds = flock[i]->GetMissileBounds();
        for (int j = 0; j < interceptorMissileBounds.size(); j++)
        {
            if (player->GetBounds().intersects(interceptorMissileBounds[j]))
            {
                //Destroy Missile
                flock[i]->DestroyMissile(j);
                //Damage Player
                break;
            }
        }
	}

    //Update Predators
    predatorFlock.Update(deltaTime, Pvector(player->GetPosition().x, player->GetPosition().y), player, asteroidSizeAndPos);
}

void FactoryFlock::Draw(sf::RenderWindow* window)
{
	//Draw Flock
	for (int i = 0; i < flock.size(); i++)
	{
		flock[i]->Draw(window);
	}

    predatorFlock.Draw(window);
}


void FactoryFlock::DrawRadarImage(sf::RenderWindow* window)
{
    for (int i = 0; i < flock.size(); i++)
    {
        flock[i]->DrawRadarImage(window);
    }

    predatorFlock.DrawRadarImage(window);
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


void FactoryFlock::DamageShip(int index)
{
    if (flock[index]->DamageShip())
        DestroyShip(index);
}

std::vector<sf::Rect<float>> FactoryFlock::GetMissileBounds()
{
    std::vector<sf::Rect<float>> missileBounds;
    if (flock.size() > 0)
    {
        for (int i = 0; i < flock.size(); i++)
        {
            std::vector<sf::Rect<float>> tempBounds = flock[i]->GetMissileBounds();
            for (int j = 0; j < tempBounds.size(); j++)
            {
                missileBounds.push_back(tempBounds[j]);
            }
        }
    }
    return missileBounds;
}

void FactoryFlock::SpawnTimer(float deltaTime)
{
    timer += deltaTime;

    if (timer >= PredatorCreationTime)
    {
        SpawnPredator();
        timer = 0;
    }
}

void FactoryFlock::SpawnPredator()
{
    int rand = std::rand() % flock.size();
    predatorFlock.AddShip(flock[rand]->GetPosition(), m_bounds);
}

std::vector<sf::Rect<float>> FactoryFlock::GetPredatorBounds()
{
    return predatorFlock.GetPredatorBounds();
}


void FactoryFlock::DestroyPredatorShip(int index)
{
    predatorFlock.DestroyShip(index);
}