#pragma once
#include <iostream>
#include "Node.h"
#include <SFML\System\Vector2.hpp>
#include <SFML/Graphics.hpp>

class Map
{
public:
	sf::Sprite* benchSprite;
	sf::Sprite* bikeSprite;
	sf::Sprite* treadMillSprite;
	Map(int tilesAlong, int tilesAcross);
	~Map();
	std::vector<Node> nodes;
	void FindNeighbors(int x, int y, Node* node, int width, int height);
	int width;
	int height;
	Node* FindNode(sf::Vector2f position);
	Node* FindNode(float x, float y);
private:
	void GenerateGym();
	sf::Texture benchTexture;
	sf::Texture bikeTexture;
	sf::Texture treadMillTexture;
};

