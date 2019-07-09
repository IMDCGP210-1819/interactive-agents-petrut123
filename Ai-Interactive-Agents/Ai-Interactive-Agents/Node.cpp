#include "pch.h"
#include "Node.h"


Node::Node(int x, int y)
{
	this->x = x;
	this->y = y;
	neighbors = std::vector<Node*>();
}

Node::Node()
{
	neighbors = std::vector<Node*>();
}


Node::~Node()
{
}

Node* Node::GetClosestNeighborToDestination(Node* nodeToCompare)
{
	sf::Vector2f diff;

	float dist;
	float minDist = FLT_MAX;
	Node* nodeToReturn = neighbors[0];
	for (size_t i = 0; i < this->neighbors.size(); i++)
	{
		diff = sf::Vector2f(neighbors[i]->x - nodeToCompare->x, neighbors[i]->y - nodeToCompare->y);
		dist = abs(sqrt(diff.x * diff.x + diff.y * diff.y));
		if (dist < minDist && (neighbors[i]->isObstacle == false || neighbors[i]->isVisited == false))
		{
			minDist = dist;
			nodeToReturn = neighbors[i];
		}
	}
	return nodeToReturn;
}

