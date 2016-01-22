#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Factory.h"
#include "Playership.h"
#include "PredatorFlock.h"
#include <vector>

class FactoryFlock 
{
public:
	FactoryFlock(int amount, sf::FloatRect bounds);
	void Update(float deltaTime, Pvector playerPos, Playership* player, std::vector<std::tuple<float, Pvector>> asteroidSizeAndPos);
	void Draw(sf::RenderWindow* window);
    void DrawRadarImage(sf::RenderWindow* window);

    void DamageShip(int index);
	void DestroyShip(int index);
    void DestroyPredatorShip(int index);
    std::vector<sf::Rect<float>> GetPredatorBounds();
	std::vector<sf::Rect<float>> GetFactoryBounds();
    std::vector<sf::Rect<float>> GetMissileBounds();

private:
    void SpawnPredator();
    void SpawnTimer(float deltaTime);

    sf::FloatRect m_bounds;
    float timer;
	std::vector<Factory*> flock;
    //Create Predators
    PredatorFlock predatorFlock;
    std::vector<InterceptorMissile*> missiles;
};