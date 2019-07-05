#include "pch.h"
#include "Agent.h"


void Agent::MoveTo()
{
	Node* currentPath = path.front();

	sf::Vector2f diff = sf::Vector2f(currentPath->x - this->m_sprite.getPosition().x, currentPath->y - this->m_sprite.getPosition().y);

	float dist = abs(sqrt(diff.x * diff.x + diff.y * diff.y));

	if (dist > 1.f) 
	{
		diff.x = diff.x / dist;
		diff.y = diff.y / dist;

		this->m_sprite.move(diff * 1.5f);
	}
	else {
		path.pop_front();
	}
	
}

void Agent::SeekFleeBehaviour(sf::Vector2i destination, bool seek)
{
	//Pass true for seek and false for flee behaviour
	float maxSpeed = 0.04f;
	sf::Vector2f desiredVelocity;
	sf::Vector2f steeringVector;

	if (seek)
	{
		desiredVelocity.x = destination.x - this->m_sprite.getPosition().x;
		desiredVelocity.y = destination.y - this->m_sprite.getPosition().y;
	}
	else
	{
		desiredVelocity.x = this->m_sprite.getPosition().x - destination.x;
		desiredVelocity.y = this->m_sprite.getPosition().y - destination.y;
	}


	//Normalization
	desiredVelocity = desiredVelocity / std::sqrt(desiredVelocity.x * desiredVelocity.x + desiredVelocity.y * desiredVelocity.y);
	desiredVelocity *= maxSpeed;

	steeringVector = desiredVelocity - velocity;

	velocity += steeringVector;

	//Normalization
	velocity = velocity / std::sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y));
	velocity *= maxSpeed;

	float angle = atan2(velocity.y, velocity.x);
	this->m_sprite.setRotation(angle * 180.0 / M_PI);

	this->m_sprite.move(velocity);

	if (this->m_sprite.getPosition().x <= 0)
	{
		this->m_sprite.setPosition(sf::Vector2f(MAP_NODE_DIMENSION_X, this->m_sprite.getPosition().y));
	}
	else if (this->m_sprite.getPosition().x >= MAP_NODE_DIMENSION_X)
	{
		this->m_sprite.setPosition(sf::Vector2f(0.0f, this->m_sprite.getPosition().y));
	}

	if (this->m_sprite.getPosition().y <= 0)
	{
		this->m_sprite.setPosition(sf::Vector2f(this->m_sprite.getPosition().x, MAP_NODE_DIMENSION_Y));
	}
	else if (this->m_sprite.getPosition().y >= MAP_NODE_DIMENSION_Y)
	{
		this->m_sprite.setPosition(sf::Vector2f(this->m_sprite.getPosition().x, 0.0f));
	}
}

sf::Vector2f Agent::lerp(sf::Vector2f start, sf::Vector2f end, float t)
{
	return (1 - t) * start + t * end;
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

	// Create a function that will return the position of an object in grid space to get the nodes for generating a path
	path = this->GeneratePath(mapReference->nodes[0], mapReference->nodes[7 * mapReference->width + 5]);
}

std::list<Node*> Agent::GeneratePath(Node start, Node end)
{
	//Pathfinding
	for (int i = 0; i < mapReference->width * mapReference->height; i++)
	{
		mapReference->nodes[i].isVisited = false;
	}

	std::list<Node*> nodeQueue;
	std::list<Node*> path;
	nodeQueue.push_back(&start);

	while (!nodeQueue.empty())
	{
		//Get the index of the first node
		int a = (nodeQueue.front()->x / MAP_NODE_DIMENSION_X) * mapReference->height + (nodeQueue.front()->y / MAP_NODE_DIMENSION_Y);
		nodeQueue.front()->isVisited = true;
		path.push_back(nodeQueue.front());

		if (nodeQueue.front()->x == end.x && nodeQueue.front()->y == end.y)
		{
			break;
		}

		nodeQueue.pop_front();

		for (size_t i = 0; i < mapReference->nodes[a].neighbors->size(); ++i)
		{
			std::vector<Node*>& vectorRef = *mapReference->nodes[a].neighbors;

			if (!vectorRef[i]->isVisited && !vectorRef[i]->isObstacle)
			{
				vectorRef[i]->isVisited = true;
				if (vectorRef[i]->x == end.x && vectorRef[i]->y == end.y)
				{
					nodeQueue.push_front(vectorRef[i]);
					break;
				}
				nodeQueue.push_back(vectorRef[i]);
			}
		}
	}
	path.pop_front();
	return path;
}

void Agent::Update()
{
	// Choose a state
	if (path.size() == 0)
	{
		ChooseTraining();
	}
	else
	{
		// We've got a path so we should move along it
		MoveTo();
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
}

Agent::~Agent()
{
}
