#ifndef TILED_BACKGROUND_H 
#define TILED_BACKGROUND_H

class TiledBackground
{
public:
	//Functions
	TiledBackground();
	TiledBackground(sf::Vector2f tiledBy, sf::Vector2f screenSize);

	void Draw(sf::RenderWindow* window);
	//Variables

protected:
	//Functions
	void Tile();

	//Variables
	sf::Vector2f m_tiledBy;
	int m_width;
	int m_height;
	std::vector<sf::Vector2f> m_tiledPositions;
	sf::Sprite m_sprite;
	sf::Texture m_texture;

private:

};

#endif