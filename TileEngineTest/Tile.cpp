#include "Tile.h"

Tile::Tile(sf::Sprite &sprite)
{
	m_Sprite = sprite;
}

void Tile::SetTilePosition(sf::Vector2f &position)
{
	this->m_Sprite.setPosition(position);
}

sf::Vector2f Tile::GetTilePosition()
{
	return this->m_Sprite.getPosition();
}

Tile::~Tile()
{

}

void Tile::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_Sprite, states);
}
