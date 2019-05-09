#pragma once
#include "Node.h"
#include <list>

class Map
{
public:
	Map(int tilesAlong, int tilesAcross);
	~Map();
	Node* nodes;
	Node FindNeighbors(int x, int y);
	int width;
	int height;
};

