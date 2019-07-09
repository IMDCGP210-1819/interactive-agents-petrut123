#include "pch.h"
#include "Agent.h"


void Agent::MoveAlongPath()
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

void Agent::Delay(float delayTimeInSeconds)
{
	sf::Clock clock;
	sf::Time time = clock.getElapsedTime();
	while (time.asSeconds() < delayTimeInSeconds)
		time += clock.restart();
}

void Agent::RunStateControl()
{
	std::cout << "Entering run state" << std::endl;
	size_t trainingCount = RandomNumberInRange(3, 1);
	for (size_t i = 0; i < trainingCount; i++)
	{
		this->energy -= RandomNumberInRange(15, 5);
		std::cout << "Training hard!" << std::endl;
		if (this->energy <= 0)
		{
			std::cout << "I don't have enough energy to continue..." << std::endl;
			this->energy = 0;
			this->currentState = Default;
			return;
		}
		//Delay(0.1f);
	}
	this->currentState = Default;
	std::cout << "Training done!" << std::endl;
}

void Agent::BenchStateControl()
{
	std::cout << "Entering bench press state" << std::endl;
	size_t trainingCount = RandomNumberInRange(5, 2);
	for (size_t i = 0; i < trainingCount; i++)
	{
		this->energy -= RandomNumberInRange(10, 5);
		std::cout << "Huh...." << std::endl;
		if (this->energy <= 0)
		{
			std::cout << "I don't have enough energy to continue..." << std::endl;
			this->energy = 0;
			this->currentState = Default;
			return;
		}
		//Delay(0.1f);
	}
	this->currentState = Default;
	std::cout << "Training done. I feel stronger already!" << std::endl;
}

void Agent::ElectricBikeStateControl()
{
	std::cout << "Started cycling" << std::endl;
	size_t trainingCount = RandomNumberInRange(7, 4);
	for (size_t i = 0; i < trainingCount; i++)
	{
		this->energy -= RandomNumberInRange(5, 2);
		if (this->energy <= 0)
		{
			std::cout << "I don't have enough energy to continue..." << std::endl;
			this->energy = 0;
			this->currentState = Default;
			return;
		}
		//Delay(0.1f);
	}
	this->currentState = Default;
	std::cout << "Training done" << std::endl;
}

void Agent::ChooseTraining()
{
	std::cout << "Choose training state" << std::endl;
	//Randomly choose the next training
	this->nextState = (States)RandomNumberInRange(5, 3);
	sf::Vector2f positionToCompare;

	// Based on the next randomly chosen state get a position for the training area
	if (this->nextState == RunState)
		positionToCompare = mapReference->treadMillSprite->getPosition();
	else if (this->nextState == BenchState)
		positionToCompare = mapReference->benchSprite->getPosition();
	else if (this->nextState == ElectricBikeState)
		positionToCompare = mapReference->bikeSprite->getPosition();
	else
		// Error handling
		std::cout << "ERROR: You got an invalid state from the radom number generator please restart!" << std::endl;

	// Create a function that will return the position of an object in grid space to get the nodes for generating a path
	if (this->m_sprite.getPosition() == positionToCompare)
	{
		// We are already in position to start training
		this->currentState = this->nextState;
		this->nextState = Default;
	}
	else
	{
		path = this->GeneratePath(*mapReference->FindNode(this->m_sprite.getPosition()), *mapReference->FindNode(positionToCompare));
		this->currentState = Move;
	}
	
	std::cout << "Training chosen" << std::endl;
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
		nodeQueue.push_back(mapReference->nodes[a].GetClosestNeighborToDestination(&end));
	}
	path.pop_front();
	return path;
}

void Agent::RestingState()
{
	std::cout << "Entering resting state!" << std::endl;
	this->energy += RandomNumberInRange(15, 5);
	this->currentState = Default;
	std::cout << "Restoring energy..." << std::endl;
}

int Agent::RandomNumberInRange(int max, int min)
{
	return rand() % (max + 1 - min) + min;
}

void Agent::Update()
{
	switch (this->currentState)
	{
		case Agent::Default:
		{
			// Do I have enough energy?
			if (this->energy >= 75)
				this->currentState = ChooseTrainingState;
			else
				this->currentState = Resting;
		}
			break;
		case Agent::Resting:
			RestingState();
			break;
		case Agent::Move:
		{
			std::cout << "Moving towards the goal" << std::endl;
			// If I arrived at the destination change the state
			if (path.size() != 0)
				MoveAlongPath();
			else
				this->currentState = this->nextState;
		}
			break;
		case Agent::RunState:
			RunStateControl();
			break;
		case Agent::BenchState:
			BenchStateControl();
			break;
		case Agent::ElectricBikeState:
			ElectricBikeStateControl();
			break;
		case Agent::ChooseTrainingState:
			ChooseTraining();
			break;
		default:
			break;
	}
	std::cout << "Energy remaining ";
	std::cout << this->energy << std::endl;
}

Agent::Agent(sf::Sprite sprite, Map* map)
{
	srand(time(0));
	this->m_sprite = sprite;
	this->mapReference = map;
	//Go into default state
	this->currentState = Default;
}

Agent::~Agent()
{
}
