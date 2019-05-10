#pragma once
#include <iostream>
#include <random>
#include "SFML/Graphics.hpp"
#include "Map.h"
#define _USE_MATH_DEFINES
#include <math.h>

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
	void MoveTo(Node start, Node end, States nextState);
	void RunStateControl();
	void BenchStateControl();
	void ElectricBikeStateControl();
	void ChooseTraining();
	sf::Sprite m_sprite;
	int RandomNumberInRange(int max, int min);
	Agent(sf::Sprite sprite, Map* map);
	~Agent();
	Map* mapReference;
	void SeekFleeBehaviour(sf::Vector2i destination, bool seek);
	sf::Vector2f velocity = sf::Vector2f(0, 0);

private:
};

