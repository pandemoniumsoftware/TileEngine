#include <SFML/Graphics.hpp>
#include <iostream>
#include "Tile.h"

int main()
{
	sf::Color transColor(255, 0, 255);

	sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML works!");

	sf::Image tileImage;
	sf::Image maskImage;

	tileImage.loadFromFile("16634.bmp");
	maskImage.loadFromFile("colormask.bmp");

	tileImage.createMaskFromColor(transColor);
	maskImage.createMaskFromColor(transColor);

	sf::Texture texture;
	sf::Texture maskTexture;
	sf::Texture wholeMapTexture;

	texture.loadFromImage(tileImage);
	maskTexture.loadFromImage(maskImage);
	wholeMapTexture.create(1024, 768);

	sf::Sprite sprite;
	sf::Sprite maskSprite;

	sprite.setTexture(texture);
	maskSprite.setTexture(maskTexture);

	int x_tiles = 1024 / Tile::TILE_WIDTH;
	int y_tiles = 768 / (Tile::TILE_HEIGHT / 2);

	std::vector<sf::Sprite*> tileMap(x_tiles*y_tiles);
	std::vector<sf::Sprite*> tilePositionMask(x_tiles*y_tiles);
	
	std::cout << "Tile map size: (" << x_tiles << ", " << y_tiles << ")" << std::endl;

	for (int i = 0; i < (x_tiles*y_tiles); i++)
	{
		tileMap[i] = new sf::Sprite(sprite);
		tilePositionMask[i] = new sf::Sprite(maskSprite);
	}

	for (int j = 0; j < y_tiles; j++)
	{
		for (int i = 0; i < x_tiles; i++)
		{
			//std::cout << "I: " << i << ", " << "J: " << j << ", I+J: " << (i*y_tiles)+j << std::endl;

			if (j % 2 == 0)
			{
				tileMap[i*y_tiles + j]->setPosition(i*Tile::TILE_WIDTH, (j*Tile::TILE_HEIGHT/2)-Tile::TILE_HEIGHT);
				tilePositionMask[i*y_tiles + j]->setPosition(i*Tile::TILE_WIDTH, (j*Tile::TILE_HEIGHT / 2) - Tile::TILE_HEIGHT);
			}
			else
			{
				tileMap[i*y_tiles + j]->setPosition(i*Tile::TILE_WIDTH + (Tile::TILE_WIDTH / 2), (j*Tile::TILE_HEIGHT / 2) - Tile::TILE_HEIGHT);
				tilePositionMask[i*y_tiles + j]->setPosition(i*Tile::TILE_WIDTH + (Tile::TILE_WIDTH / 2), (j*Tile::TILE_HEIGHT / 2) - Tile::TILE_HEIGHT);
			}

			// This will severely break if i or j ever exceeds 255; however, this shouldn't happen...
			sf::Uint8 iVal = static_cast<sf::Uint8>(i);
			sf::Uint8 jVal = static_cast<sf::Uint8>(j);

			sf::Color maskColor{ iVal, 0, jVal };
			tilePositionMask[i*y_tiles + j]->setColor(maskColor);
		
			//std::cout << "Tile position: " << i*Tile::TILE_WIDTH << ", " << j*Tile::TILE_HEIGHT << std::endl;
			

		}
	}

	bool mouseHeldDown = false;
	bool firstLoad = false;
	sf::Image mapImage;
	mapImage.create(1024, 768, sf::Color::Black);
	sf::Color pixColor{};

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		for (auto Sprite : tilePositionMask)
		{
			window.draw(*Sprite);
		}

		if (!firstLoad)
		{
			wholeMapTexture.update(window);
			mapImage = wholeMapTexture.copyToImage();
			firstLoad = true;
			std::cout << "Attempted to update wholeMapTex" << std::endl;
		}

		for (auto Sprite : tileMap)
		{
			window.draw(*Sprite);
		}

		if (event.type == sf::Event::MouseButtonPressed && !mouseHeldDown)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				mouseHeldDown = true;
				
				std::cout << "Left mouse clicked at (" << event.mouseButton.x << ", " << event.mouseButton.y << ")" << std::endl;
				//std::cout << "Tile column: " << event.mouseButton.x / Tile::TILE_WIDTH << std::endl;
				//std::cout << "Tile row: " << event.mouseButton.y / Tile::TILE_HEIGHT << std::endl;
				
				pixColor = mapImage.getPixel(event.mouseButton.x, event.mouseButton.y);
				int rVal = static_cast<int>(pixColor.r);
				int gVal = static_cast<int>(pixColor.g);
				int bVal = static_cast<int>(pixColor.b);

				std::cout << "Map value is: " << rVal << ", " << bVal << std::endl;
			}
		} 

		if (event.type == sf::Event::MouseButtonReleased)
		{
			mouseHeldDown = false;
		}

		

		window.display();

	}

	//delete tileMap;
	//tile_test = nullptr;
		
	return 0;
}