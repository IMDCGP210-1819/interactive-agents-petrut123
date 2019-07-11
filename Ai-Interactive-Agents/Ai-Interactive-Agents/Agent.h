#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Map.h"
#include <math.h>
#include "SFML/System/Clock.hpp"
#include "Random.h"

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

private:
	int energy = Random::RandomNumberInRange(100, 30);
	std::list<Node*> path;
	Map* mapReference;

	void RestingState();
	void MoveAlongPath();
	void RunStateControl();
	void BenchStateControl();
	void ElectricBikeStateControl();
	void ChooseTraining();
	std::list<Node*> GeneratePath(Node start, Node end);
	sf::Vector2f lerp(sf::Vector2f start, sf::Vector2f end, float t);
	void Delay(float delayTimeInSeconds);
};

