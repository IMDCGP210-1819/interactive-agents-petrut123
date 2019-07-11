#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Agent.h"
#include "Map.h"
#include "GymTrainer.h"

using namespace std;

const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 600;
const int AGENT_COUNT = 3;

std::vector<Agent*> agents;

Map* worldMap;

void DrawCalls(sf::RenderWindow* window)
{
	window->draw(*worldMap->benchSprite);
	window->draw(*worldMap->bikeSprite);
	window->draw(*worldMap->treadMillSprite);

	for (size_t i = 0; i < AGENT_COUNT; i++)
		window->draw(agents[i]->m_sprite);
}

int main()
{
	sf::Texture guyTexture;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Interactive Agents!");

	//window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	worldMap = new Map(WINDOW_WIDTH / MAP_NODE_DIMENSION_X, WINDOW_HEIGHT / MAP_NODE_DIMENSION_Y);

	// Load texture
	guyTexture.loadFromFile("../Assets/guy.png");

	// Create agents
	agents.resize(AGENT_COUNT);
	for (size_t i = 0; i < AGENT_COUNT; i++)
		agents[i] = new Agent(sf::Sprite(guyTexture), worldMap);

	// Create gym trainer
	GymTrainer trainer = GymTrainer(sf::Sprite(guyTexture));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		for (size_t i = 0; i < agents.size(); i++)
			agents[i]->Update();

		trainer.Update();
		window.clear(sf::Color(255, 111, 97, 100));
		window.draw(trainer.m_sprite);
		DrawCalls(&window);
		window.display();
	}

	return 0;
}
