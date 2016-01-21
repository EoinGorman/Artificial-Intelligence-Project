#include "AsteroidField.h"

/*
public:
AsteroidField(int amount, sf::FloatRect bounds);
void Update(float deltaTime);
void Draw(sf::RenderWindow* window);
sf::FloatRect GetBounds();

private:
std::vector<Asteroid*> m_asteroids;
*/

AsteroidField::AsteroidField(int amount, sf::FloatRect bounds)
{
    for (int i = 0; i < amount; i++)
    {
        sf::Vector2f randPos(std::rand() % (int)bounds.width, std::rand() % (int)bounds.height);
        sf::Vector2f randDir(((std::rand() % 200) - 100) / 100.0f, ((std::rand() % 200) - 100) / 100.0f);
        sf::Vector2f randScale = GetValidScale();
        m_asteroids.push_back(new Asteroid(randPos, randDir, randScale, bounds));
    }
}

sf::Vector2f AsteroidField::GetValidScale()
{
    float scale = ((std::rand() % 400) - 200) / 100.0f;
    sf::Vector2f randScale(scale, scale);
    if (scale == 0)
    {
        randScale = GetValidScale();
    }

    return randScale;
}

void AsteroidField::Update(float deltaTime)
{
    for (int i = 0; i < m_asteroids.size(); i++)
    {
        m_asteroids[i]->Update(deltaTime);
    }
}

void AsteroidField::Draw(sf::RenderWindow* window)
{
    for (int i = 0; i < m_asteroids.size(); i++)
    {
        m_asteroids[i]->Draw(window);
    }
}

std::vector<sf::Rect<float>> AsteroidField::GetBounds()
{
    std::vector<sf::Rect<float>> asteroidFieldBounds;
    if (m_asteroids.size() > 0)
    {
        for (int i = 0; i < m_asteroids.size(); i++)
        {
            asteroidFieldBounds.push_back(m_asteroids[i]->GetBounds());
        }
    }

    return asteroidFieldBounds;
}

std::vector<std::tuple<float, Pvector>>  AsteroidField::GetSizeAndPosition()
{
    std::vector<std::tuple<float, Pvector>> asteroidSizeAndPosition;
    if (m_asteroids.size() > 0)
    {
        for (int i = 0; i < m_asteroids.size(); i++)
        {
            asteroidSizeAndPosition.push_back(m_asteroids[i]->GetSizeAndPosition());
        }
    }

    return asteroidSizeAndPosition;
}