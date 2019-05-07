#pragma once
#include "SFML/Graphics.hpp"
class Agent : public sf::Drawable
{
public:
	enum States
	{
		Idle,
		Move,
		CheckIn,
		RunState,
		BenchState,
		ElectricBikeState
	};
	sf::Transformable *transform = new sf::Transformable();
	States currentState = Idle;
	void MoveTo(sf::Vector3f targetPosition);
	void CheckInState();
	void RunState();
	void BenchState();
	void ElectricBikeState();
	Agent();
	~Agent();

private:
	sf::Sprite m_sprite;
};

