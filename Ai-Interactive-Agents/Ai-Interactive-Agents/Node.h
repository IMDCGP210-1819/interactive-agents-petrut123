#pragma once
#include <list>
#include <vector>
#include <SFML/System/Vector2.hpp>

//Constants
const int MAP_NODE_DIMENSION_X = 60;
const int MAP_NODE_DIMENSION_Y = 30;

struct Node
{
public:
	Node(int x, int y);
	Node();
	~Node();
	bool isVisited = false;
	bool isObstacle = false;
	//Position in grid
	int x, y;
	std::vector<Node*> neighbors;
	Node* GetClosestNeighborToDestination(Node* nodeToCompare);
};

