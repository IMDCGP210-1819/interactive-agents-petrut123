#include "pch.h"
#include "Map.h"


Map::Map(int xDimension, int yDimension)
{
	//this->nodes = new Node[xDimension * yDimension];
	this->nodes = std::vector<Node>();
	this->nodes.resize(xDimension * yDimension);
	this->width = xDimension;
	this->height = yDimension;

	int index = 0;
	for (int i = 0; i < xDimension; i++)
	{
		for (int j = 0; j < yDimension; j++)
		{
			nodes[index].x = i * MAP_NODE_DIMENSION_X;
			nodes[index].y = j * MAP_NODE_DIMENSION_Y;
			//nodes[index].neighbors = *FindNeighbors(i, j);
			FindNeighbors(i, j, &nodes[index], width, height);
			//std::cout << i << " ";
			//std::cout << j << std::endl;
			index++;
		}
	}
}

void Map::FindNeighbors(int x, int y, Node* node, int width, int height)
{
	//std::vector<Node> neighbors;
	//We check if the node is placed at the edge of the map since that changes its neighbors
	if (x == 0 && y == 0)
	{
		node->neighbors = new std::vector<Node*>[3];
		//node->neighbors->resize();
		node->neighbors->push_back(&nodes[1]);
		node->neighbors->push_back(&nodes[(height)]);
		node->neighbors->push_back(&nodes[(height)+1]);
	}
	else if (x == 0 && y != 0)
	{
		if (y == height - 1)
		{
			node->neighbors = new std::vector<Node*>[3];
			//node->neighbors->resize(3);
			node->neighbors->push_back(&nodes[y - 1]);
			node->neighbors->push_back(&nodes[height + y - 1]);
			node->neighbors->push_back(&nodes[height + y]);
		}
		else
		{
			node->neighbors = new std::vector<Node*>[5];
			//node->neighbors->resize(5);
			node->neighbors->push_back(&nodes[y - 1]);
			node->neighbors->push_back(&nodes[height + y - 1]);
			node->neighbors->push_back(&nodes[height + y]);
			node->neighbors->push_back(&nodes[y + 1]);
			node->neighbors->push_back(&nodes[height + y + 1]);
		}
	}
	else if (x != 0 && y == 0)
	{
		if (x == width - 1)
		{
			node->neighbors = new std::vector<Node*>[3];
			//node->neighbors->resize(3);
			node->neighbors->push_back(&nodes[(x - 1) * height]);
			node->neighbors->push_back(&nodes[(x - 1) * height + 1]);
			node->neighbors->push_back(&nodes[x * height + 1]);
		}
		else
		{
			node->neighbors = new std::vector<Node*>[5];
			//node->neighbors->resize(5);
			node->neighbors->push_back(&nodes[(x - 1) * height]);
			node->neighbors->push_back(&nodes[(x - 1) * height + 1]);
			node->neighbors->push_back(&nodes[x * height + 1]);
			node->neighbors->push_back(&nodes[(x + 1) * height]);
			node->neighbors->push_back(&nodes[(x + 1) * height + 1]);
		}
	}
	else if (y == height - 1)
	{
		if (x == width - 1)
		{
			node->neighbors = new std::vector<Node*>[3];
			//node->neighbors->resize(3);
			node->neighbors->push_back(&nodes[(x - 1) * height + y]);
			node->neighbors->push_back(&nodes[(x - 1) * height + y - 1]);
			node->neighbors->push_back(&nodes[x * height + y - 1]);
		}
		else
		{
			node->neighbors = new std::vector<Node*>[5];
			//node->neighbors->resize(5);
			node->neighbors->push_back(&nodes[(x - 1) * height + y]);
			node->neighbors->push_back(&nodes[(x - 1) * height + y - 1]);
			node->neighbors->push_back(&nodes[x * height + y - 1]);
			node->neighbors->push_back(&nodes[(x + 1) * height + y]);
			node->neighbors->push_back(&nodes[(x + 1) * height + y - 1]);
		}
	}
	else if (x == width - 1)
	{
		node->neighbors = new std::vector<Node*>[5];
		//node->neighbors->resize(5);
		node->neighbors->push_back(&nodes[x * height - 1]);
		node->neighbors->push_back(&nodes[x * height + 1]);
		node->neighbors->push_back(&nodes[(x - 1) * height - 1]);
		node->neighbors->push_back(&nodes[(x - 1) * height]);
		node->neighbors->push_back(&nodes[(x - 1) * height + 1]);
	}
	else
	{
		node->neighbors = new std::vector<Node*>[8];
		//node->neighbors->resize(8);
		node->neighbors->push_back(&nodes[(x - 1) * height + y - 1]);
		node->neighbors->push_back(&nodes[(x - 1) * height + y]);
		node->neighbors->push_back(&nodes[(x - 1) * height + y + 1]);
		node->neighbors->push_back(&nodes[x * height + y - 1]);
		node->neighbors->push_back(&nodes[x * height + y + 1]);
		node->neighbors->push_back(&nodes[(x + 1) * height + y - 1]);
		node->neighbors->push_back(&nodes[(x + 1) * height + y]);
		node->neighbors->push_back(&nodes[(x + 1) * height + y + 1]);
	}
	//return &neighbors;
}

Map::~Map()
{
}


