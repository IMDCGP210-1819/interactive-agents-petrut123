#include "pch.h"
#include "Map.h"


Map::Map(int xDimension, int yDimension)
{
	this->nodes = new Node[xDimension * yDimension];
	this->width = xDimension;
	this->height = yDimension;

	int index = 0;
	for (int i = 0; i < xDimension; i++)
	{
		for (int j = 0; j < yDimension; j++)
		{
			Node node = Node(i * MAP_NODE_DIMENSION_X, j * MAP_NODE_DIMENSION_Y);
			nodes[index] = node;
			nodes[index].neighbors = FindNeighbors(i, j);
			index++;
		}
	}
}

Map::~Map()
{
}

Node Map::FindNeighbors(int x, int y)
{
	//TODO change [] of nodes with list<Node>
	Node returnNeighbors;

	//We check if the node is placed at the edge of the map since that changes its neighbors
	if (x == 0 && y == 0)
	{
		returnNeighbors =  Node[3];
		//x * height + y
		returnNeighbors[0] = nodes[1];
		returnNeighbors[1] = nodes[height];
		returnNeighbors[2] = nodes[height + 1];
	}
	else if (x == 0 && y != 0)
	{
		if (y == height - 1)
		{
			returnNeighbors = new Node[3];
			returnNeighbors[0] = nodes[y - 1];
			returnNeighbors[1] = nodes[height + y - 1];
			returnNeighbors[2] = nodes[height + y];
		}
		else
		{
			returnNeighbors = new Node[5];
			returnNeighbors[0] = nodes[y - 1];
			returnNeighbors[1] = nodes[height + y - 1];
			returnNeighbors[2] = nodes[height + y];
			returnNeighbors[3] = nodes[y + 1];
			returnNeighbors[4] = nodes[height + y + 1];
		}
	}
	else if (x != 0 && y == 0)
	{
		if (x == width - 1)
		{
			returnNeighbors = new Node[3];
			returnNeighbors[0] = nodes[x - 1 * height];
			returnNeighbors[1] = nodes[x - 1 * height + 1];
			returnNeighbors[2] = nodes[x * height + 1];
		}
		else
		{
			returnNeighbors = new Node[5];
			returnNeighbors[0] = nodes[x - 1 * height];
			returnNeighbors[1] = nodes[x - 1 * height + 1];
			returnNeighbors[2] = nodes[x * height + 1];
			returnNeighbors[3] = nodes[x + 1 * height];
			returnNeighbors[4] = nodes[x + 1 * height + 1];
		}
	}
	else if (y == height - 1)
	{
		if (x == width - 1)
		{
			returnNeighbors = new Node[3];
			returnNeighbors[0] = nodes[x - 1 * height];
			returnNeighbors[1] = nodes[x - 1 * height - 1];
			returnNeighbors[1] = nodes[x * height - 1];
		}
		else
		{
			returnNeighbors = new Node[5];
			returnNeighbors[0] = nodes[x - 1 * height];
			returnNeighbors[1] = nodes[x - 1 * height - 1];
			returnNeighbors[2] = nodes[x * height - 1];
			returnNeighbors[3] = nodes[x + 1 * height - 1];
			returnNeighbors[4] = nodes[x + 1 * height];
		}
	}
	else if (x == width - 1)
	{
		returnNeighbors = new Node[5];
		returnNeighbors[0] = nodes[x * height - 1];
		returnNeighbors[1] = nodes[x * height + 1];
		returnNeighbors[2] = nodes[x - 1 * height - 1];
		returnNeighbors[3] = nodes[x - 1 * height];
		returnNeighbors[4] = nodes[x - 1 * height + 1];
	}
	else
	{
		returnNeighbors = new Node[8];
		returnNeighbors[0] = nodes[x - 1 * height + y - 1];
		returnNeighbors[1] = nodes[x - 1 * height + y];
		returnNeighbors[2] = nodes[x - 1 * height + y + 1];
		returnNeighbors[3] = nodes[x * height + y - 1];
		returnNeighbors[4] = nodes[x * height + y + 1];
		returnNeighbors[5] = nodes[x + 1 * height + y - 1];
		returnNeighbors[6] = nodes[x + 1 * height + y];
		returnNeighbors[7] = nodes[x + 1 * height + y + 1];
	}
	return returnNeighbors;
}
