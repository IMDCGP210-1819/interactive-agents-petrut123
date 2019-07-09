#pragma once
#include <iostream>
#include <random>
#include "SFML/Graphics.hpp"
#include "Map.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "SFML/System/Clock.hpp"

class Agent
{
public:
	void Update();

	enum States
	{
		Default,
		Resting,
		Move,
		RunState,
		BenchState,
		ElectricBikeState,
		ChooseTrainingState
	};

	States currentState;
	States nextState;
	sf::Sprite m_sprite;
	Agent(sf::Sprite sprite, Map* map);
	~Agent();
	sf::Vector2f velocity = sf::Vector2f(0, 0);

private:
	int energy = RandomNumberInRange(100, 30);
	std::list<Node*> path;
	Map* mapReference;

	void RestingState();
	void SeekFleeBehaviour(sf::Vector2i destination, bool seek);
	void MoveAlongPath();
	void RunStateControl();
	void BenchStateControl();
	void ElectricBikeStateControl();
	void ChooseTraining();
	std::list<Node*> GeneratePath(Node start, Node end);
	int RandomNumberInRange(int max, int min);
	sf::Vector2f lerp(sf::Vector2f start, sf::Vector2f end, float t);
};

