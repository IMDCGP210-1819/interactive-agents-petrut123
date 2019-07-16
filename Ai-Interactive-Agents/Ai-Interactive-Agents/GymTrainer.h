#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Random.h"
#include "Node.h"
#include "Agent.h"

class GymTrainer
{
public:
	GymTrainer(sf::Sprite sprite, std::vector<Agent*> agents);
	void Update();
	void OnClick();
	sf::Sprite m_sprite;
private:
	bool personChosen = false;
	bool selected = false;
	int chosenAgentIndex;
	std::vector<Agent*> agentsReferences;
	sf::Vector2i targetPosition = sf::Vector2i(0, 0);
	sf::Vector2f velocity = sf::Vector2f(0, 0);
	void SeekFleeBehaviour(sf::Vector2i destination, bool seek);
};

