#include "pch.h"
#include "GymTrainer.h"



GymTrainer::GymTrainer(sf::Sprite sprite)
{
	this->m_sprite = sprite;
	this->targetPosition = sf::Vector2i(Random::RandomNumberInRange(1200, 0), Random::RandomNumberInRange(600, 0));
}

void GymTrainer::Update()
{
	SeekFleeBehaviour(targetPosition, true);

	// Check if the gym trainer got to it's destination
	if (abs(this->m_sprite.getPosition().x - this->targetPosition.x) < 1 && abs(this->m_sprite.getPosition().y - this->targetPosition.y) < 1)
	{
		this->targetPosition = sf::Vector2i(Random::RandomNumberInRange(1200, 0), Random::RandomNumberInRange(600, 0));
		std::cout << "Destination Reached" << std::endl;
	}
}

// Pass true for seek and false for flee behaviour
void GymTrainer::SeekFleeBehaviour(sf::Vector2i destination, bool seek)
{
	
	float maxSpeed = 2.f;
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

	/*if (this->m_sprite.getPosition().x <= 0)
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
	}*/
}