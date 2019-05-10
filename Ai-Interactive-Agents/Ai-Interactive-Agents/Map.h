#pragma once
#include <iostream>
#include "Node.h"

class Map
{
public:
	Map(int tilesAlong, int tilesAcross);
	~Map();
	std::vector<Node> nodes;
	void FindNeighbors(int x, int y, Node* node, int width, int height);
	int width;
	int height;
};

