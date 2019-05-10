#pragma once
#include <list>
#include <vector>

//Constants
const int MAP_NODE_DIMENSION_X = 60;
const int MAP_NODE_DIMENSION_Y = 30;

struct Node
{
public:
	Node(int x, int y);
	Node();
	~Node();
	//void FindNeighbors(int x, int y, std::vector<Node>* nodes, int width, int height);
	bool isVisited = false;
	bool isObstacle = false;
	//Position in grid
	int x, y;
	std::vector<Node*>* neighbors;
};

