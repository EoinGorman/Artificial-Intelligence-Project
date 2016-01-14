#ifndef SPACESHIP 
#define SPACESHIP

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#define PI 3.14159265
class Spaceship
{
public:
	//Functions
	Spaceship();
	Spaceship(sf::Vector2f pos, sf::Vector2f dir, sf::FloatRect bounds);

	void Update(float deltaTime);
	void Draw(sf::RenderWindow* window);
	sf::Vector2f GetPosition();
	//Variables

protected:
	//Functions
	void Move(float deltaTime);
	void WrapAroundScreen();

	//Variables
	int m_width;
	int m_height;
	float m_speed;
	sf::Vector2f m_position;
	sf::Vector2f m_direction;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::FloatRect m_bounds;

private:

};

#endif