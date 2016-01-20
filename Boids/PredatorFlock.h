#include <iostream>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Predator.h"
#include "Playership.h"
#include <vector>


#ifndef PREDATORFLOCK_H_
#define PREDATORFLOCK_H_


class PredatorFlock
{
public:
	PredatorFlock(int amount, sf::FloatRect bounds);
	void Update(float deltaTime, Pvector playerPos, Playership* player);
	void Draw(sf::RenderWindow* window);
    void DrawRadarImage(sf::RenderWindow* window);

	void DestroyShip(int index);
	std::vector<sf::Rect<float>> GetPredatorBounds();

private:
	std::vector<Predator*> flock;
};
#endif