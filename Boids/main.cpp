#include <iostream>
#include <vector>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <string>
#include "InputManager.h"
#include "tiledBackground.h"
#include "Spaceship.h"
#include "Playership.h"
#include "Boid.h"
#include "Pvector.h"
#include "Flock.h"

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
	//const int window_height = 500;
	//const int window_width = 500;

	//Having the style of "None" gives a false-fullscreen effect for easier closing and access.
	//No FPS limit of V-sync setting needed for it may cause unnecessary slowdown.
	sf::RenderWindow window(sf::VideoMode(window_width, window_height, desktop.bitsPerPixel), "Dec & Snugs Super Project", sf::Style::None);

	sf::View fixed = window.getView(); // The 'fixed' view will never change

	sf::View standard = fixed; // The 'standard' view will be the game world

	sf::Clock deltaClock;

	//Create Game Objects
	TiledBackground background(sf::Vector2f(3,3), sf::Vector2f(window_width, window_height));

	Playership player(sf::Vector2f(window_width/2, window_height/2), sf::Vector2f(1, 0), sf::FloatRect(-window_width, -window_height, window_width * 3, window_height * 3));

	//Create flock, vector of shapes, and initialize boids
	Flock flock;
	vector<sf::CircleShape> shapes;

	for (int i = 0; i < 50; i++) //Number of boids is hardcoded for testing pusposes.
	{
		//Boid b(rand() % window_width, rand() % window_height); //Starts the boid with a random position in the window.
		Boid b(window_width / 3, window_height / 3); //Starts all boids in the center of the screen
		sf::CircleShape shape(8, 3); //Shape with a radius of 10 and 3 points (Making it a triangle)

									 //Changing the Visual Properties of the shape
									 //shape.setPosition(b.location.x, b.location.y); //Sets position of shape to random location that boid was set to.
		shape.setPosition(window_width, window_height); //Testing purposes, starts all shapes in the center of screen.
		shape.setOutlineColor(sf::Color(0, 255, 0));
		shape.setFillColor(sf::Color::Green);
		shape.setOutlineColor(sf::Color::White);
		shape.setOutlineThickness(1);
		shape.setRadius(boidsSize);

		//Adding the boid to the flock and adding the shapes to the vector<sf::CircleShape>
		flock.addBoid(b);
		shapes.push_back(shape);
	}

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
		if (InputManager::GetInstance()->IsKeyDown(sf::Keyboard::Space))
		{
			if (action == "flock")
				action = "swarm";
			else
				action = "flock";
		}
		player.Update(deltaClock.getElapsedTime().asSeconds());

		deltaClock.restart();
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

		//Draws all of the Boids out, and applies functions that are needed to update.
		for (int i = 0; i < shapes.size(); i++)
		{
			window.draw(shapes[i]);

			//Cout's removed due to slowdown and only needed for testing purposes
			//cout << "Boid "<< i <<" Coordinates: (" << shapes[i].getPosition().x << ", " << shapes[i].getPosition().y << ")" << endl;
			//cout << "Boid Code " << i << " Location: (" << flock.getBoid(i).location.x << ", " << flock.getBoid(i).location.y << ")" << endl;

			//Matches up the location of the shape to the boid
			shapes[i].setPosition(flock.getBoid(i).location.x, flock.getBoid(i).location.y);

			// Calculates the angle where the velocity is pointing so that the triangle turns towards it.
			float theta;
			theta = flock.getBoid(i).angle(flock.getBoid(i).velocity);
			shapes[i].setRotation(theta);

			// These if statements prevent boids from moving off the screen through warpping
			// If boid exits right boundary
			if (shapes[i].getPosition().x > window_width)
				shapes[i].setPosition(shapes[i].getPosition().x - window_width, shapes[i].getPosition().y);
			// If boid exits bottom boundary
			if (shapes[i].getPosition().y > window_height)
				shapes[i].setPosition(shapes[i].getPosition().x, shapes[i].getPosition().y - window_height);
			// If boid exits left boundary
			if (shapes[i].getPosition().x < 0)
				shapes[i].setPosition(shapes[i].getPosition().x + window_width, shapes[i].getPosition().y);
			// If boid exits top boundary
			if (shapes[i].getPosition().y < 0)
				shapes[i].setPosition(shapes[i].getPosition().x, shapes[i].getPosition().y + window_height);
		}

		//Applies the three rules to each boid in the flock and changes them accordingly.
		if (action == "flock")
			flock.flocking();
		else
			flock.swarming();

		//Updates the window with current values of any data that was modified.
		window.display();

	//This loop continues until window is closed. Continues the process of updating, drawing, rendering the boids, and the window.
	}
	return 0;

}