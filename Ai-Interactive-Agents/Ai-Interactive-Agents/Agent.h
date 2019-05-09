#pragma once
#include <iostream>
#include <random>
#include "SFML/Graphics.hpp"
#include "Map.h"

class Agent
{
public:
	enum States
	{
		Idle,
		Move,
		RunState,
		BenchState,
		ElectricBikeState,
		ChooseTrainingState
	};

	States currentState;
	void MoveTo(Node start, States nextState);
	void RunStateControl();
	void BenchStateControl();
	void ElectricBikeStateControl();
	void ChooseTraining();
	sf::Sprite m_sprite;
	int RandomNumberInRange(int max, int min);
	Agent(sf::Sprite sprite, Map* map);
	~Agent();
	Map* mapReference;

private:
};

