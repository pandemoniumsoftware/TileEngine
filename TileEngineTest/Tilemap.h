#include "Tile.h"
#include <vector>
#pragma once
class Tilemap
{
public:
	Tilemap();
	~Tilemap();
private:
	std::vector<Tile> tiles;
};

