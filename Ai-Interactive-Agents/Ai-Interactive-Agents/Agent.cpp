#include "pch.h"
#include "Agent.h"


void Agent::MoveTo(Node start, States nextState)
{
	//TODO Pathfinding
	for (int i = 0; i < mapReference->width * mapReference->height; i++)
	{
		mapReference->nodes[i].isVisited = false;
	}

	std::list<Node> nodeQueue;
	nodeQueue.push_back(start);

	while (!nodeQueue.empty())
	{
		// Dequeue a vertex from queue and print it 
		//std::cout << nodeQueue.front(); << " ";

		//Get the index of the first node
		int a = nodeQueue.front().x * mapReference->height + nodeQueue.front().y;
		nodeQueue.front().isVisited = true;
		std::cout << nodeQueue.front().x << " ";
		std::cout << nodeQueue.front().y << std::endl;
		nodeQueue.pop_front();

		// Get all adjacent vertices of the dequeued 
		// vertex s. If a adjacent has not been visited,  
		// then mark it visited and enqueue it 
		for (int i = 0; i < sizeof(mapReference->nodes[a].neighbors); ++i)
		{
			if (!mapReference->nodes[a].neighbors[i].isVisited && !mapReference->nodes[a].neighbors[i].isObstacle)
			{
				mapReference->nodes[a].neighbors[i].isVisited = true;
				nodeQueue.push_back(mapReference->nodes[a].neighbors[i]);
			}
		}
	}
}

void Agent::RunStateControl()
{
}

void Agent::BenchStateControl()
{
}

void Agent::ElectricBikeStateControl()
{
}

void Agent::ChooseTraining()
{
	currentState = ChooseTrainingState;
	//Randomly choose the next training
	States nextState = (States)RandomNumberInRange(4, 2);
	MoveTo(mapReference->nodes[10, 7], ChooseTrainingState);
	if (nextState == RunState)
	{
		//MoveTo();
	}
}

int Agent::RandomNumberInRange(int max, int min)
{
	srand(time(0));
	return rand() % (max + 1 - min) + min;
}
Agent::Agent(sf::Sprite sprite, Map* map)
{
	this->m_sprite = sprite;
	this->mapReference = map;
	//Go into idle state;
	currentState = Idle;
	//Start interacting
	ChooseTraining();
}

Agent::~Agent()
{
}
