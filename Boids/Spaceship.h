#ifndef SPACESHIP 
#define SPACESHIP

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Pvector.h"

#define PI 3.14159265
class Spaceship
{
public:
	//Functions
	Spaceship();
	Spaceship(sf::Vector2f pos, sf::Vector2f dir, sf::FloatRect bounds);

	void Update(float deltaTime);
	void Draw(sf::RenderWindow* window);
    void DrawRadarImage(sf::RenderWindow* window);
	sf::Vector2f GetPosition();
    sf::Rect<float> Spaceship::GetBounds();
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
    sf::Sprite m_radarSprite;
    sf::Texture m_radarTexture;
	sf::FloatRect m_bounds;

private:

};

#endif