#ifndef BULLET_H
#define BULLET_H

class Bullet
{
public:
	Bullet();
	Bullet(sf::Vector2f pos, float angle, sf::FloatRect bounds);

	void Update(float deltaTime);
	void Draw(sf::RenderWindow* window);
	bool OutOfBounds();
	sf::Vector2f GetPosition();

private:
	//Functions
	void Move(float deltaTime);
	void CheckBounds();

	//Variables
	bool offScreen;
	int m_width;
	int m_height;
	float m_speed;
	sf::Vector2f m_position;
	sf::Vector2f m_direction;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::FloatRect m_bounds;	//level bounds
};

#endif