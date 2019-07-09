#include "pch.h"
#include "Map.h"


Map::Map(int xDimension, int yDimension)
{
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
			FindNeighbors(i, j, &nodes[index], width, height);
			index++;
		}
	}
	GenerateGym();
}

void Map::FindNeighbors(int x, int y, Node* node, int width, int height)
{
	//std::vector<Node> neighbors;
	//We check if the node is placed at the edge of the map since that changes its neighbors
	if (x == 0 && y == 0)
	{
		//node->neighbors[3];
		//node->neighbors.resize(3);
		node->neighbors.push_back(&nodes[1]);
		node->neighbors.push_back(&nodes[(height)]);
		node->neighbors.push_back(&nodes[(height)+1]);
	}
	else if (x == 0 && y != 0)
	{
		if (y == height - 1)
		{
			//node->neighbors[3];
		    //node->neighbors.resize(3);
			node->neighbors.push_back(&nodes[y - 1]);
			node->neighbors.push_back(&nodes[height + y - 1]);
			node->neighbors.push_back(&nodes[height + y]);
		}
		else
		{
			//node->neighbors[5];
			//node->neighbors.resize(5);
			node->neighbors.push_back(&nodes[y - 1]);
			node->neighbors.push_back(&nodes[height + y - 1]);
			node->neighbors.push_back(&nodes[height + y]);
			node->neighbors.push_back(&nodes[y + 1]);
			node->neighbors.push_back(&nodes[height + y + 1]);
		}
	}
	else if (x != 0 && y == 0)
	{
		if (x == width - 1)
		{
			//node->neighbors[3];
			//node->neighbors.resize(3);
			node->neighbors.push_back(&nodes[(x - 1) * height]);
			node->neighbors.push_back(&nodes[(x - 1) * height + 1]);
			node->neighbors.push_back(&nodes[x * height + 1]);
		}
		else
		{
			//node->neighbors[5];
			//node->neighbors.resize(5);
			node->neighbors.push_back(&nodes[(x - 1) * height]);
			node->neighbors.push_back(&nodes[(x - 1) * height + 1]);
			node->neighbors.push_back(&nodes[x * height + 1]);
			node->neighbors.push_back(&nodes[(x + 1) * height]);
			node->neighbors.push_back(&nodes[(x + 1) * height + 1]);
		}
	}
	else if (y == height - 1)
	{
		if (x == width - 1)
		{
			//node->neighbors[3];
			//node->neighbors.resize(3);
			node->neighbors.push_back(&nodes[(x - 1) * height + y]);
			node->neighbors.push_back(&nodes[(x - 1) * height + y - 1]);
			node->neighbors.push_back(&nodes[x * height + y - 1]);
		}
		else
		{
			//node->neighbors[5];
			//node->neighbors.resize(5);
			node->neighbors.push_back(&nodes[(x - 1) * height + y]);
			node->neighbors.push_back(&nodes[(x - 1) * height + y - 1]);
			node->neighbors.push_back(&nodes[x * height + y - 1]);
			node->neighbors.push_back(&nodes[(x + 1) * height + y]);
			node->neighbors.push_back(&nodes[(x + 1) * height + y - 1]);
		}
	}
	else if (x == width - 1)
	{
		//node->neighbors[5];
		//node->neighbors.resize(5);
		node->neighbors.push_back(&nodes[x * height - 1]);
		node->neighbors.push_back(&nodes[x * height + 1]);
		node->neighbors.push_back(&nodes[(x - 1) * height - 1]);
		node->neighbors.push_back(&nodes[(x - 1) * height]);
		node->neighbors.push_back(&nodes[(x - 1) * height + 1]);
	}
	else
	{
		//node->neighbors[8];
		//node->neighbors.resize(8);
		node->neighbors.push_back(&nodes[(x - 1) * height + y - 1]);
		node->neighbors.push_back(&nodes[(x - 1) * height + y]);
		node->neighbors.push_back(&nodes[(x - 1) * height + y + 1]);
		node->neighbors.push_back(&nodes[x * height + y - 1]);
		node->neighbors.push_back(&nodes[x * height + y + 1]);
		node->neighbors.push_back(&nodes[(x + 1) * height + y - 1]);
		node->neighbors.push_back(&nodes[(x + 1) * height + y]);
		node->neighbors.push_back(&nodes[(x + 1) * height + y + 1]);
	}
}

Node* Map::FindNode(sf::Vector2f position)
{
	for (size_t i = 0; i < this->nodes.size(); i++)
	{
		// Calculate the distance and compare it with a node's size to see if the position to compare it's inside the node's rectangle
		if (abs(this->nodes[i].x - position.x) <= MAP_NODE_DIMENSION_X && abs(this->nodes[i].y - position.y) <= MAP_NODE_DIMENSION_Y)
			return &this->nodes[i];
	}
	return NULL;
}

Node* Map::FindNode(float x, float y)
{
	return FindNode(sf::Vector2f(x, y));
}

void Map::GenerateGym()
{
	benchTexture;
	bikeTexture;
	treadMillTexture;

	// Loading sprites
	benchTexture.loadFromFile("../Assets/benchpress.png");
	bikeTexture.loadFromFile("../Assets/bike.png");
	treadMillTexture.loadFromFile("../Assets/run.png");

	this->benchSprite = new sf::Sprite(benchTexture);
	this->bikeSprite = new sf::Sprite(bikeTexture);
	this->treadMillSprite = new sf::Sprite(treadMillTexture);

	this->benchSprite->setPosition(sf::Vector2f(this->nodes[7 * this->width + 6].x, this->nodes[7 * this->width + 6].y));
	this->bikeSprite->setPosition(sf::Vector2f(this->nodes[12 * this->width + 2].x, this->nodes[12 * this->width + 2].y));
	this->treadMillSprite->setPosition(sf::Vector2f(this->nodes[17 * this->width + 15].x, this->nodes[17 * this->width + 15].y));

	this->nodes[7 * this->width + 6].isObstacle = true;
	this->nodes[12 * this->width + 2].isObstacle = true;
	this->nodes[17 * this->width + 15].isObstacle = true;
}

Map::~Map()
{
}


