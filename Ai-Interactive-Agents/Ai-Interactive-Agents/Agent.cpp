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

std::string Agent::ConvertStateToString(States state)
{
	std::string stringToReturn;
	switch (state)
	{
	case Agent::Default:
		stringToReturn = "Default State!";
		break;
	case Agent::Resting:
		stringToReturn = "Resting State!";
		break;
	case Agent::Move:
		stringToReturn = "Moving State!";
		break;
	case Agent::RunState:
		stringToReturn = "Running on the treadmill!";
		break;
	case Agent::BenchState:
		stringToReturn = "Weight lifting State!";
		break;
	case Agent::ElectricBikeState:
		stringToReturn = "Cycling on the electric bike!";
		break;
	case Agent::ChooseTrainingState:
		stringToReturn = "Choose Training State!";
		break;
	default:
		break;
	}

	return stringToReturn;
}

void Agent::RunStateControl()
{
	//std::cout << "Entering run state" << std::endl;
	size_t trainingCount = Random::RandomNumberInRange(3, 1);
	for (size_t i = 0; i < trainingCount; i++)
	{
		this->energy -= Random::RandomNumberInRange(15, 5);
		//std::cout << "Training hard!" << std::endl;
		if (this->energy <= 0)
		{
			//std::cout << "I don't have enough energy to continue..." << std::endl;
			this->energy = 0;
			this->currentState = Default;
			return;
		}
		//Delay(0.1f);
	}
	this->currentState = Default;
	//std::cout << "Training done!" << std::endl;
}

void Agent::BenchStateControl()
{
	//std::cout << "Entering bench press state" << std::endl;
	size_t trainingCount = Random::RandomNumberInRange(5, 2);
	for (size_t i = 0; i < trainingCount; i++)
	{
		this->energy -= Random::RandomNumberInRange(10, 5);
		//std::cout << "Huh...." << std::endl;
		if (this->energy <= 0)
		{
			//std::cout << "I don't have enough energy to continue..." << std::endl;
			this->energy = 0;
			this->currentState = Default;
			return;
		}
		//Delay(0.1f);
	}
	this->currentState = Default;
	//std::cout << "Training done. I feel stronger already!" << std::endl;
}

void Agent::ElectricBikeStateControl()
{
	//std::cout << "Started cycling" << std::endl;
	size_t trainingCount = Random::RandomNumberInRange(7, 4);
	for (size_t i = 0; i < trainingCount; i++)
	{
		this->energy -= Random::RandomNumberInRange(5, 2);
		if (this->energy <= 0)
		{
			//std::cout << "I don't have enough energy to continue..." << std::endl;
			this->energy = 0;
			this->currentState = Default;
			return;
		}
		//Delay(0.1f);
	}
	this->currentState = Default;
	//std::cout << "Training done" << std::endl;
}

void Agent::ChooseTraining()
{
	//std::cout << "Choose training state" << std::endl;
	//Randomly choose the next training
	this->nextState = (States)Random::RandomNumberInRange(5, 3);
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
	
	//std::cout << "Training chosen" << std::endl;
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
	//std::cout << "Entering resting state!" << std::endl;
	while (this->energy <= 100)
	{
		RestoreEnergy(Random::RandomNumberInRange(15, 5));
	}
	Delay(0.05f);
	this->currentState = Default;
	//std::cout << "Restoring energy..." << std::endl;
}

void Agent::Update()
{
	switch (this->currentState)
	{
		case Agent::Default:
		{
			// Do I have enough energy?
			if (this->energy >= 100)
				this->currentState = ChooseTrainingState;
			else 
			{
				this->nextState = Resting;
				this->currentState = Move;
				// Generate a path towards the Resting Zone
				path = GeneratePath(*mapReference->FindNode(this->m_sprite.getPosition()), *mapReference->FindNode(50.f, 50.f));
			}	
		}
			break;
		case Agent::Resting:
			RestingState();
			break;
		case Agent::Move:
		{
			//std::cout << "Moving towards the goal" << std::endl;
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

	if (selected)
	{
		std::cout << "Energy remaining " << this->energy << std::endl;
		std::cout << "Current state: " << ConvertStateToString(this->currentState) << std::endl;
		if (currentState == Move)
			std::cout << "Moving towards the place for my next state: " << ConvertStateToString(this->nextState) << std::endl;
		std::cout << "___________________________________________________" << std::endl;
		std::cout<<std::endl;
	}
}

void Agent::OnAgentClicked()
{
	selected = !selected;
	if (selected)
		std::cout << "Agent selected! " << std::endl;
	else
		std::cout << "Agent deselected! " << std::endl;
}

void Agent::RestoreEnergy(int energy)
{
	this->energy += energy;
}

Agent::Agent(sf::Sprite sprite, Map* map)
{
	this->m_sprite = sprite;
	this->mapReference = map;

	// Go into default state
	this->currentState = Default;
}

Agent::~Agent()
{
}
