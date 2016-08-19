#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#pragma once
class Tile : public sf::Drawable
{
public:
	Tile(sf::Sprite & sprite);
	void SetTilePosition(sf::Vector2f &position);
	sf::Vector2f GetTilePosition();
	~Tile();
	static const int TILE_HEIGHT = 15;
	static const int TILE_WIDTH = 32;
private:
	sf::Sprite m_Sprite;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

