#pragma once
#include <iostream>
#include <random>
#include "SFML/Graphics.hpp"
#include "Map.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "SFML/System/Clock.hpp"

class Agent : public sf::Transformable
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
	void MoveTo();
	void RunStateControl();
	void BenchStateControl();
	void ElectricBikeStateControl();
	void ChooseTraining();
	std::list<Node*> GeneratePath(Node start, Node end);
	void Update();
	sf::Sprite m_sprite;
	int RandomNumberInRange(int max, int min);
	Agent(sf::Sprite sprite, Map* map);
	~Agent();
	Map* mapReference;
	void SeekFleeBehaviour(sf::Vector2i destination, bool seek);
	sf::Vector2f velocity = sf::Vector2f(0, 0);
	sf::Vector2f lerp(sf::Vector2f start, sf::Vector2f end, float t);

private:
	std::list<Node*> path;
};

