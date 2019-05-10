#include "pch.h"
#include "Agent.h"


void Agent::MoveTo(Node start, Node end, States nextState)
{
	//Pathfinding
	for (int i = 0; i < mapReference->width * mapReference->height; i++)
	{
		mapReference->nodes[i].isVisited = false;
	}

	std::list<Node*> nodeQueue;
	nodeQueue.push_back(&start);

	while (!nodeQueue.empty())
	{
		//Get the index of the first node
		int a = (nodeQueue.front()->x / MAP_NODE_DIMENSION_X) * mapReference->height + (nodeQueue.front()->y / MAP_NODE_DIMENSION_Y);
		nodeQueue.front()->isVisited = true;

		if (nodeQueue.front() == &end)
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
				if (vectorRef[i] == &end)
				{
					nodeQueue.push_front(vectorRef[i]);
					this->m_sprite.setPosition(sf::Vector2f(vectorRef[i]->x, vectorRef[i]->y));
					break;
				}
				nodeQueue.push_back(vectorRef[i]);
				this->m_sprite.setPosition(sf::Vector2f(vectorRef[i]->x, vectorRef[i]->y));
				std::cout << this->m_sprite.getPosition().x << " ";
				std::cout << this->m_sprite.getPosition().y << std::endl;
			}
		}
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
	this->m_sprite.setRotation(angle * 180.0f / M_PI);

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
	MoveTo(mapReference->nodes[0], mapReference->nodes[7 * mapReference->height + 5], ChooseTrainingState);
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
