#pragma once
//Constants
const int MAP_NODE_DIMENSION_X = 60;
const int MAP_NODE_DIMENSION_Y = 30;

class Node
{
public:
	Node(int x, int y);
	Node();
	~Node();
	bool isVisited = false;
	bool isObstacle = false;
	//Position in grid
	int x, y;
	Node* neighbors;
};

