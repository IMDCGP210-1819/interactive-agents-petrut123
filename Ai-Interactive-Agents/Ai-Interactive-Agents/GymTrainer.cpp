#include "pch.h"
#include "GymTrainer.h"



GymTrainer::GymTrainer(sf::Sprite sprite, std::vector<Agent*> agents)
{
	this->m_sprite = sprite;
	this->targetPosition = sf::Vector2i(Random::RandomNumberInRange(1200, 0), Random::RandomNumberInRange(600, 0));
	this->agentsReferences = agents;
}

void GymTrainer::Update()
{
	SeekFleeBehaviour(targetPosition, true);
	

	if (personChosen)
	{
		this->chosenAgentIndex = Random::RandomNumberInRange(agentsReferences.size() - 1, 0);
		this->targetPosition = (sf::Vector2i)agentsReferences[this->chosenAgentIndex]->m_sprite.getPosition();
		//std::cout << "Chose an agent to restore energy " << std::endl;

		if (abs(this->m_sprite.getPosition().x - this->targetPosition.x) < 1 && abs(this->m_sprite.getPosition().y - this->targetPosition.y) < 1)
		{
			this->agentsReferences[chosenAgentIndex]->RestoreEnergy(15);
			personChosen = false;

			if (selected)
				std::cout << "Restored Energy to Agent" << std::endl;

			// Choose a new target position
			this->targetPosition = sf::Vector2i(Random::RandomNumberInRange(1200, 0), Random::RandomNumberInRange(600, 0));
		}
	}
	else
	{
		// Check if the gym trainer got to it's destination
		if (abs(this->m_sprite.getPosition().x - this->targetPosition.x) < 1 && abs(this->m_sprite.getPosition().y - this->targetPosition.y) < 1)
		{
			this->targetPosition = sf::Vector2i(Random::RandomNumberInRange(1200, 0), Random::RandomNumberInRange(600, 0));
			//std::cout << "Destination Reached" << std::endl;

			if (Random::RandomNumberInRange(100, 0) <= 30)
				personChosen = true;
		}
	}

	if (selected)
	{
		if (personChosen)
			std::cout << "Going towards an Agent to restore it's energy " << std::endl;
		else
			std::cout << "Moving in the Gym " << std::endl;
	}
}

void GymTrainer::OnClick()
{
	selected = !selected;
	if (selected)
		std::cout << "Trainer selected " << std::endl;
	else
		std::cout << "Trainer deselected " << std::endl;
}

// Pass true for seek and false for flee behaviour
void GymTrainer::SeekFleeBehaviour(sf::Vector2i destination, bool seek)
{
	
	float maxSpeed = 1.f;
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

	//float angle = atan2(velocity.y, velocity.x);
	//this->m_sprite.setRotation(angle * 180.0 / M_PI);

	this->m_sprite.move(velocity);
}