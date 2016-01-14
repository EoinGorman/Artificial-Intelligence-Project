#include <iostream>
#include <vector>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <string>
#include "InputManager.h"
#include "tiledBackground.h"
#include "Spaceship.h"
#include "Playership.h"
#include "Pvector.h"
#include "Swarm.h"

using namespace std;

void ClampCamera(sf::View* view, float windowWidth, float windowHeight)
{
	sf::Vector2f newCenter = view->getCenter();
	//X Axis
	if (view->getCenter().x <= -windowWidth * 0.5f)
	{
		newCenter.x = -windowWidth * 0.5f;
	}

	else if (view->getCenter().x >= windowWidth * 1.5f)
	{
		newCenter.x = windowWidth * 1.5f;
	}

	//Y Axis
	if (view->getCenter().y <= -windowHeight * 0.5f)
	{
		newCenter.y = -windowHeight * 0.5f;
	}

	else if (view->getCenter().y >= windowHeight * 1.5f)
	{
		newCenter.y = windowHeight * 1.5f;
	}

	view->setCenter(newCenter);
}

int main()
{
	float boidsSize = 3;
	string action = "flock";

	//Gets the resolution, size, and bits per pixel for the screen of the PC that is running this program.
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	const int window_height = desktop.height;
	const int window_width = desktop.width;

	//Having the style of "None" gives a false-fullscreen effect for easier closing and access.
	//No FPS limit of V-sync setting needed for it may cause unnecessary slowdown.
	sf::RenderWindow window(sf::VideoMode(window_width, window_height, desktop.bitsPerPixel), "Dec & Snugs Super Project", sf::Style::None);

	sf::View fixed = window.getView(); // The 'fixed' view will never change

	sf::View standard = fixed; // The 'standard' view will be the game world

	sf::Clock deltaClock;

	//Create Game Objects
	TiledBackground background(sf::Vector2f(3,3), sf::Vector2f(window_width, window_height));

	Playership player(sf::Vector2f(window_width/2, window_height/2), sf::Vector2f(1, 0), sf::FloatRect(-window_width, -window_height, window_width * 3, window_height * 3));

	//Create swarm
	Swarm swarm(50, sf::FloatRect(-window_width, -window_height, window_width * 3, window_height * 3));

	while (window.isOpen())
	{
		//Event used to close program when window is closed
		sf::Event event;
		while (window.pollEvent(event))
		{
			//"close requested" event: we close the window
			//Implemented alternate ways to close the window.
			InputManager::GetInstance()->UpdatePolledEvents(event);
			if ((event.type == sf::Event::Closed) || 
				InputManager::GetInstance()->IsKeyDown(sf::Keyboard::Escape))
			{
				window.close();
			}
		}

		//check for mouse click, draws and adds boid to flock if so.
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			//Gets mouse coordinates
			sf::Vector2i mouseCoords = sf::Mouse::getPosition(window);
		}

		//UPDATE HERE!!! 

		float deltaTime = deltaClock.getElapsedTime().asSeconds();
		player.Update(deltaTime);

		deltaClock.restart();

		swarm.Update(deltaTime, Pvector(player.GetPosition().x, player.GetPosition().y));

		InputManager::GetInstance()->UpdateState();

		//Clears previous frames of visualization to not have clutter. (And simulate animation)
		window.clear();

		//DRAW HERE!!!

		//If player is inside a certain "inner bounds" of level
		standard.setCenter(player.GetPosition());	//Set camera to center on player
		ClampCamera(&standard, window_width, window_height);

		window.setView(standard);
		background.Draw(&window);
		player.Draw(&window);
		swarm.Draw(&window);

		//Updates the window with current values of any data that was modified.
		window.display();
	//This loop continues until window is closed. Continues the process of updating, drawing, rendering the boids, and the window.
	}
	return 0;

}