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
#include "FactoryFlock.h"
#include "PredatorFlock.h"

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
	srand(time(NULL));	//Initialise the random seed
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
    sf::View radar = fixed;
    radar.setViewport(sf::FloatRect(0.01f, 0.79f, 0.2, 0.2));
    radar.zoom(3);

    //Create radar background
    sf::Texture texture;
    texture.loadFromFile("../Images/RadarBackground.png");
    sf::Sprite sprite;
    sprite.setTexture(texture, true);
    sprite.setOrigin(sf::Vector2f(sprite.getLocalBounds().width / 2 , sprite.getLocalBounds().height / 2));
    sprite.setScale((window_width / sprite.getLocalBounds().width) * 3, (window_height / sprite.getLocalBounds().height) * 3);
    sprite.setPosition(window_width / 2, window_height / 2);

	sf::Clock deltaClock;

	//Create Game Objects
	TiledBackground background(sf::Vector2f(3,3), sf::Vector2f(window_width, window_height));

	Playership player(sf::Vector2f(window_width/2, window_height/2), sf::Vector2f(1, 0), sf::FloatRect(-window_width, -window_height, window_width * 3, window_height * 3));

	//Create swarm
	Swarm swarm(40, sf::FloatRect(-window_width, -window_height, window_width * 3, window_height * 3));

	//Create Factories
	FactoryFlock factoryFlock(5, sf::FloatRect(-window_width, -window_height, window_width * 3, window_height * 3));

	//Create Predators
	PredatorFlock predatorFlock(10, sf::FloatRect(-window_width, -window_height, window_width * 3, window_height * 3));

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


        //Get all bounding boxes
        std::vector<sf::FloatRect> bulletBounds = player.GetBulletBounds();
        std::vector<sf::FloatRect> swarmBounds = swarm.GetSwarmBounds();
        std::vector<sf::FloatRect> factoryBounds = factoryFlock.GetFactoryBounds();
		std::vector<sf::FloatRect> predatorBounds = predatorFlock.GetPredatorBounds();
        sf::FloatRect playerBound = player.GetBounds();

        //Calculate Delta Time
		float deltaTime = deltaClock.getElapsedTime().asSeconds();
		deltaClock.restart();

        //Call Updates
		player.Update(deltaTime);
		swarm.Update(deltaTime, Pvector(player.GetPosition().x, player.GetPosition().y));
		factoryFlock.Update(deltaTime, Pvector(player.GetPosition().x, player.GetPosition().y), &player);
		predatorFlock.Update(deltaTime, Pvector(player.GetPosition().x, player.GetPosition().y), &player);

		//COLLISION

        //Collision between player and swarm
        for (int i = 0; i < swarmBounds.size(); i++)
        {
            if (playerBound.intersects(swarmBounds[i]))
            {
                //Damage player
                swarm.DestroyShip(i);
                goto endPLayerSwamrCol;
            }
        }
    endPLayerSwamrCol:

        //Collision with player bullets
        for (int i = 0; i < bulletBounds.size(); i++)
        {
            //Bullets + Factories
            for (int j = 0; j < factoryBounds.size(); j++)
            {
                if (bulletBounds[i].intersects(factoryBounds[j]))
                {
                    player.DestroyBullet(i);
                    factoryFlock.DamageShip(j);  //Damage Factory
                    goto endBulletFactoryCol;
                }
            }
			//Bullets + Predators
			for (int j = 0; j < predatorBounds.size(); j++)
			{
				if (bulletBounds[i].intersects(predatorBounds[j]))
				{
					player.DestroyBullet(i);
					predatorFlock.DestroyShip(j);  //Destroy Pred
					goto endBulletPredatorCol;
				}
			}
            //Bullets + Swarm
            for (int j = 0; j < swarmBounds.size(); j++)
            {
                if (bulletBounds[i].intersects(swarmBounds[j]))
                {
                    player.DestroyBullet(i);
                    swarm.DestroyShip(j);
                    goto endBulletSwarmCol;
                }
            }
        }
    endBulletFactoryCol:
    endBulletSwarmCol:
	endBulletPredatorCol:
		//Predators and Player
		for (int i = 0; i < predatorBounds.size(); i++)
		{
			if (playerBound.intersects(predatorBounds[i]))
			{
				//Damage player
				predatorFlock.DestroyShip(i);
				goto endPlayerPredatorCol;
			}
		}
	endPlayerPredatorCol:
        //Factories and Player
        for (int i = 0; i < factoryBounds.size(); i++)
        {
            if (playerBound.intersects(factoryBounds[i]))
            {
                //Damage player
                factoryFlock.DestroyShip(i);
                goto endPlayerFactoryCol;
            }
        }
	endPlayerFactoryCol:
	

		InputManager::GetInstance()->UpdateState();

		//Clears previous frames of visualization to not have clutter. (And simulate animation)
		window.clear();

		//DRAW HERE!!!

		//If player is inside a certain "inner bounds" of level
		standard.setCenter(player.GetPosition());	//Set camera to center on player
		ClampCamera(&standard, window_width, window_height);

        //Set to draw in game view
		window.setView(standard);

		background.Draw(&window);
		player.Draw(&window);
		swarm.Draw(&window);
		factoryFlock.Draw(&window);
		predatorFlock.Draw(&window);
		

        //Set to draw in radar view
        window.setView(radar);
        window.draw(sprite);
        swarm.DrawRadarImage(&window);
        player.DrawRadarImage(&window);
        factoryFlock.DrawRadarImage(&window);
        predatorFlock.DrawRadarImage(&window);

		//Updates the window with current values of any data that was modified.
		window.display();
	//This loop continues until window is closed. Continues the process of updating, drawing, rendering the boids, and the window.
	}
	return 0;

}